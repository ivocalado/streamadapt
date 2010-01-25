/*
 * facade.cpp
 *
 *  Created on: 28/12/2009
 *      Author: ivocalado
 */

#include <facade.h>
#include <logger/consoleappender.h>
#include <logger/logger.h>
#include <infrafactory.h>
#include <trpsession.h>
#include <ostream>
#include <policyengine.h>

//using namespace infrastream;
using namespace AdaptationPolicy;

namespace infrastream {

Facade* infrastream::Facade::instance = 0;

Facade::Facade() {

#ifdef USE_LOGGER
	setLogLevel(LOG_INFO);
	addAppender(new infralog::ConsoleAppender);
#endif

}

Facade::Facade(const Facade&) {
}

Facade& Facade::operator=(Facade&) {
	return *this;
}

Facade::~Facade() {
	// TODO Auto-generated destructor stub
}

string Facade::getName() const {
	return "Name";
}

Facade* Facade::getInstance() {
	if (!instance)
		instance = new Facade;
	return instance;
}

SessionManager* Facade::createClientSession(string targetIp, int targetPort,
		GenericSenderSocket* sender, GenericReceiverSocket* receiver,
		string pluginPath, map<string, string> * additionalParams)
		throw(CannotCreateSessionException, CannotLoadPolicyException) {

	PolicyEngine* engine = 0;
	SessionManager* session = 0;

	try {
		auto_ptr<PolicyConfigurationType> _plugin = loadPolicy(pluginPath);
		PolicyConfigurationType *plugin = new PolicyConfigurationType(*(_plugin.get()));

		engine = new PolicyEngine;
		//	PluginNegotiationPtrlIF* negotiation =
		//			InfraFactory::getInstance()->buildNegotiationSession(); TODO DESCOMENTAR
		session = new SessionManager(sender, receiver, engine);
		TransportSession* trSession =
				InfraFactory::getInstance()->buildTransportSession(0, plugin,
						*engine, targetIp, targetPort,
						InfraFactory::CLIENT_SESSION, session);
		//StreamSession* ssession = InfraFactory::getInstance()



		session->setTransportSession(trSession);


		session->startSession();
	} catch (...) {
		if (engine) {
			delete engine;
			log_info("Exception on creating session. Deleting engine");
		}
		throw ;
	}
	return session;
}

#include <iostream>
SessionManager* Facade::createServerSession(string localIP, int localport,
		GenericSenderSocket* sender, GenericReceiverSocket* receiver,
		string pluginPath, map<string, string> * additionalParams)
throw(CannotCreateSessionException, CannotLoadPolicyException) {
	PolicyEngine* engine = 0;
		SessionManager* session = 0;

		try {
			auto_ptr<PolicyConfigurationType> plugin = loadPolicy(pluginPath);



			engine = new PolicyEngine;
//
//			//	PluginNegotiationPtrlIF* negotiation =
//			//			InfraFactory::getInstance()->buildNegotiationSession(); TODO DESCOMENTAR
			session = new SessionManager(sender, receiver, engine);
//
			TransportSession* trSession =
					InfraFactory::getInstance()->buildTransportSession(0, plugin.get(),
							*engine, localIP, localport,
							InfraFactory::SERVER_SESSION, session);
//
//			//StreamSession* ssession = InfraFactory::getInstance()
//
//
//
			session->setTransportSession(trSession);

		} catch (...) {
			if (engine) {
				delete engine;
				log_info("Exception on creating session. Deleting engine");
			}
			throw ;
		}

		return session;

}

auto_ptr<PolicyConfigurationType> Facade::loadPolicy(string policyPath)
throw(CannotLoadPolicyException) {
	try {
		return auto_ptr<PolicyConfigurationType> (adaptation_policy(
						policyPath.c_str()));
	} catch (const xml_schema::exception& e) {
		ostringstream s;
		s << e;
		throw CannotLoadPolicyException(s.str());
	}
}
}

