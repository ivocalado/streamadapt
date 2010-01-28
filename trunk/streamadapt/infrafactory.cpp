/*
 * infrafactory.cpp
 *
 *  Created on: 30/12/2009
 *      Author: ivocalado
 */

#include <infrafactory.h>
#include <policyengine.h>
#include <string>
#include <map>
#include <ostream>
#include <adaptationjob.h>
#include <jobmanager.h>

namespace infrastream {

InfraFactory* InfraFactory::instance = 0;

InfraFactory* InfraFactory::getInstance() {
	if (!instance)
		instance = new InfraFactory;
	return instance;
}

PluginNegotiationPtrlIF* InfraFactory::buildNegotiationSession() {
	return 0;
}

TransportSession* InfraFactory::buildTransportSession(
		PluginNegotiationPtrlIF* negotiation,
		PolicyConfigurationType* policyDesc, PolicyEngine& engine,
		string ip, int port, InfraFactory::SessionType sessionType,
		ConnectionListener* listener) throw(CannotCreateSessionException,
		InvalidPolicyException) {

	startup_config::transport_type* tProperties =
			&policyDesc->startup_config().transport();

	string transportProtocol = tProperties->protocol();
	log_info("Protocol: " + transportProtocol);

	string pluginName = tProperties->plugin_name();
	log_info("Plugin Name: " + pluginName);

	string libName = tProperties->library_name();
	log_info("lib Name: " + libName);

	TransportSession* session = new TransportSession(transportProtocol,
			pluginName, libName, &engine, negotiation);

	adapt_config::transport_type *adapt = 0;

	bool useAdaptation = tProperties->enable_adaptation();

	if (useAdaptation) {
		if (policyDesc->adapt_config().present()
				&& policyDesc->adapt_config().get().transport().present())
			adapt = &policyDesc->adapt_config().get().transport().get();
		else {
			log_error("Invalid policy in InfraFactory::buildTransportSession");
			delete session;
			throw InvalidPolicyException("You must provide adaptation config. "
				"Otherwise set the adaptation as false");
		}
		session->setPolicy(adapt);
	}

	bool useDirInfo = tProperties->library_directory().present();

	PluginManager* pm = PluginManager::getInstance();

	PluginTransportIF* plugin = (useDirInfo) ? pm->findAdaptor<
			PluginTransportIF> (pluginName, libName,
			tProperties->library_directory().get()) : pm->findAdaptor<
			PluginTransportIF> (pluginName, libName);

	checkAndLog(plugin->getName(), pluginName, false,
			"The protocols specified are different. Make your checks", log_warning);

	try {
		if (sessionType == SERVER_SESSION) {
			plugin->buildSession(ip, port, listener);
		} else {
			plugin->buildSession();
			plugin->addDestination(ip, port);
			plugin->sendData(0); //Send a silent packet to open socket
		}
	} catch (...) {
		delete session;
		log_error("invalid Session");
		throw CannotCreateSessionException();
	}

	if (tProperties->provides().present()) {
		startup_config::transport_type::provides_type::provide_iterator
				provideIt(tProperties->provides().get().provide().begin());
		for (; provideIt != tProperties->provides().get().provide().end(); ++provideIt) {
			EventType et(*provideIt);
			EventType det(__default_value(*provideIt));
			Event de(det, provideIt->default_value());
			unsigned int timestamp = provideIt->update_time();
			engine.registerProvider(et, timestamp, plugin, de);
		}
	}
//
	JobManager::getInstance()->addJob(new AdaptationJob<
			startup_config::transport_type, PluginTransportIF,
			PluginNegotiationPtrlIF> (tProperties, *plugin, 0));

	plugin->startSession();
	session->setTSession(plugin);

	return session;
}

StreamSession* InfraFactory::buildStreamSession(
		PluginNegotiationPtrlIF* negotiation,
		PolicyConfigurationType* policyDesc, PolicyEngine& engine)
		throw (CannotCreateSessionException, InvalidPolicyException) {

	startup_config::stream_type* sProperties =
			&policyDesc->startup_config().stream();

	string pluginName = sProperties->plugin_name();
	log_info("Plugin Name: " + pluginName);

	string libName = sProperties->library_name();
	log_info("lib Name: " + libName);

	StreamSession *session = new StreamSession(pluginName, libName, &engine,
			negotiation);

	adapt_config::stream_type *adapt = 0;

	bool useAdaptation = sProperties->enable_adaptation();

	if (useAdaptation) {
		if (policyDesc->adapt_config().present()
				&& policyDesc->adapt_config().get().stream().present())
			adapt = &policyDesc->adapt_config().get().stream().get();
		else {
			log_error("Invalid policy in InfraFactory::buildStreamSession");
			delete session;
			throw InvalidPolicyException("You must provide adaptation config. "
				"Otherwise set the adaptation as false");
		}
		session->setPolicy(adapt);
	}

	bool useDirInfo = sProperties->library_directory().present();

	PluginManager* pm = PluginManager::getInstance();

	PluginStreamIF* plugin = (useDirInfo) ? pm->findAdaptor<
			PluginStreamIF> (pluginName, libName,
			sProperties->library_directory().get()) : pm->findAdaptor<
			PluginStreamIF> (pluginName, libName);

	checkAndLog(plugin->getName(), pluginName, false,
			"The protocols specified are different. Make your checks", log_warning);

	int transmissionType =
			sProperties->transmission_properties().transmission_type();

	if (sProperties->transmission_properties().audio_transmission().present()) {
		PluginStreamIF::StreamType st;

		switch (transmissionType) {
		case (startup_config::stream_type::transmission_properties_type::transmission_type_type::half_receive):
			st = PluginStreamIF::DECODER_SIDE;
			break;
		case (startup_config::stream_type::transmission_properties_type::transmission_type_type::half_transmit):
			st = PluginStreamIF::ENCODER_SIDE;
			break;
		case (startup_config::stream_type::transmission_properties_type::transmission_type_type::full_duplex):
			st = PluginStreamIF::BOTH_SIDES;
			break;
		};

		try{
		plugin->buildSession(
				st,
				sProperties->transmission_properties().audio_transmission().get().codec_name(),
				sProperties->transmission_properties().audio_transmission().get().enable_preprocessing());
		}catch(...){
			log_error("Erro on build session")
		}

	} else {
		///TODO build video SESSION

	}

	if (sProperties->provides().present()) {
		startup_config::stream_type::provides_type::provide_iterator provideIt(
				sProperties->provides().get().provide().begin());
		for (; provideIt != sProperties->provides().get().provide().end(); ++provideIt) {
			EventType et(*provideIt);
			EventType det(__default_value(*provideIt));
			Event de(det, provideIt->default_value());
			unsigned int timestamp = provideIt->update_time();
			engine.registerProvider(et, timestamp, plugin, de);
		}
	}

	JobManager::getInstance()->addJob(new AdaptationJob<
			startup_config::stream_type, PluginStreamIF,
			PluginNegotiationPtrlIF> (sProperties, *plugin, 0));

	session->setSSession(plugin);
	return session;

}

InfraFactory::InfraFactory() {
	// TODO Auto-generated constructor stub

}

InfraFactory::~InfraFactory() {
	// TODO Auto-generated destructor stub
}

}
