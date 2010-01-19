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
		auto_ptr<PolicyConfigurationType> policyDesc, PolicyEngine& engine,
		string targetIP, int targetPort, string serverIp, int serverPort)
		throw(CannotCreateSessionException, InvalidPolicyException) {

	startup_config::transport_type& tProperties =
			policyDesc->startup_config().transport();

	string transportProtocol = tProperties.protocol();
	log_info("Protocol: " + transportProtocol);

	string pluginName = tProperties.plugin_name();
	log_info("Plugin Name: " + pluginName);

	string libName = tProperties.library_name();
	log_info("lib Name: " + libName);

	TransportSession* session = new TransportSession(transportProtocol,
			pluginName, libName, &engine, negotiation);

	adapt_config::transport_type *adapt = 0;

	bool useAdaptation = tProperties.enable_adaptation();

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

	bool useDirInfo = tProperties.library_directory().present();

	PluginManager* pm = PluginManager::getInstance();

	auto_ptr<PluginTransportIF> plugin = (useDirInfo) ? pm->findAdaptor<
			PluginTransportIF> (pluginName, libName,
			tProperties.library_directory().get()) : pm->findAdaptor<
			PluginTransportIF> (pluginName, libName);

	checkAndLog(plugin->getName(), pluginName, false,
			"The protocols specified are different. Make your checks", log_warning);

	try {
		if (serverIp == "" || !serverPort)
			plugin->buildSession();
		else
			plugin->buildSession(serverIp, serverPort);
	} catch (...) {
		delete session;
		log_error("invalid Session");
		throw CannotCreateSessionException();
	}

	plugin->addDestination(targetIP, targetPort);

	plugin->sendData(0); //Send a silent packet to open socket


	if (tProperties.provides().present()) {
		startup_config::transport_type::provides_type::provide_iterator
				provideIt(tProperties.provides().get().provide().begin());
		for (; provideIt != tProperties.provides().get().provide().end(); ++provideIt) {
			EventType et(*provideIt);
			EventType det(__default_value(*provideIt));
			Event de(det, provideIt->default_value());
			unsigned int timestamp = provideIt->update_time();
			engine.registerProvider(et, timestamp, plugin.get(), de);
		}
	}

	JobManager::getInstance()->addJob(new AdaptationJob<
			startup_config::transport_type, auto_ptr<PluginTransportIF> > (
			tProperties, plugin));
	//	configurePlugin(tProperties, plugin);

	plugin->startSession();
	session->setTSession(plugin);

	return session;
}

InfraFactory::InfraFactory() {
	// TODO Auto-generated constructor stub

}

InfraFactory::~InfraFactory() {
	// TODO Auto-generated destructor stub
}

}
