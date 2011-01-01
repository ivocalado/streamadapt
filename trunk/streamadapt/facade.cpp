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
		string policyPath, map<string, string> * additionalParams)
		throw(CannotCreateSessionException, CannotLoadPolicyException) {

	PolicyEngine* engine = 0;
	SessionManager* session = 0;
	PolicyConfigurationType* policyDesc = 0;
	TransportSession* trSession = 0;
	StreamSession* ssession = 0;

	try {
		auto_ptr<PolicyConfigurationType> pd = loadPolicy(policyPath);
		policyDesc = new PolicyConfigurationType(*(pd.get()));

		engine = new PolicyEngine;
		//	PluginNegotiationPtrlIF* negotiation =
		//			InfraFactory::getInstance()->buildNegotiationSession(); TODO DESCOMENTAR
		session = new SessionManager(sender, receiver, engine, policyDesc);

		trSession = InfraFactory::getInstance()->buildTransportSession(0,
				policyDesc, *engine, targetIp, targetPort,
				InfraFactory::CLIENT_SESSION, session);

		session->setTransportSession(trSession);

		ssession = InfraFactory::getInstance()->buildStreamSession(0,
				policyDesc, *engine);

		session->setStreamSession(ssession);

		session->startSession();
	} catch (...) {
		if (session) {
			delete session;
			log_error("Exception on creating session. Deleting Session manager object");
		}

		if (engine) {
			delete engine;
			log_info("Exception on creating session. Deleting engine");
		}

		if (policyDesc) {
			delete policyDesc;
			log_error("Exception on creating session. Deleting plugin object");
		}

		throw;
	}
	return session;
}

SessionManager* Facade::createServerSession(string localIP, int localport,
		GenericSenderSocket* sender, GenericReceiverSocket* receiver,
		string policyPath, map<string, string> * additionalParams)
throw(CannotCreateSessionException, CannotLoadPolicyException) {

	PolicyEngine* engine = 0;
	SessionManager* session = 0;
	PolicyConfigurationType* policyDesc = 0;
	TransportSession* trSession = 0;
	StreamSession* ssession = 0;

	try {
		auto_ptr<PolicyConfigurationType> pd = loadPolicy(policyPath);
		policyDesc = new PolicyConfigurationType(*(pd.get()));
		engine = new PolicyEngine;
		session = new SessionManager(sender, receiver, engine, policyDesc);
		trSession =
		InfraFactory::getInstance()->buildTransportSession(0, policyDesc,
				*engine, localIP, localport,
				InfraFactory::SERVER_SESSION, session);
		session->setTransportSession(trSession);

		ssession = InfraFactory::getInstance()->buildStreamSession(0,
				policyDesc, *engine);

		session->setStreamSession(ssession);
	} catch (...) {
		if(session) {
			delete session;
			log_error("Exception on creating session. Deleting Session manager object");
		}

		if (engine) {
			delete engine;
			log_info("Exception on creating session. Deleting engine");
		}

		if(policyDesc) {
			delete policyDesc;
			log_error("Exception on creating session. Deleting plugin object");
		}

		throw;
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

