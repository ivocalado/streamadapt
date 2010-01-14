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

GenericSenderSocket* Facade::createSession(string localIP, int localport,
		string targetIp, int targetPort, string pluginPath,
		GenericReceiverSocket* listener, map<string, string> * additionalParams)
		throw(CannotCreateSessionException, CannotLoadPolicyException) {

	auto_ptr<PolicyConfigurationType> plugin = loadPolicy(pluginPath);

	infrastream::GenericSenderSocket* sender = new GenericSenderSocket;

	PluginNegotiationPtrlIF* negotiation =
			InfraFactory::getInstance()->buildNegotiationSession();

	TransportSession* trSession =
			InfraFactory::getInstance()->buildTransportSession(negotiation,
					plugin, sender->getEngine(), targetIp, targetPort, localIP,
					localport);

	//StreamSession* ssession = InfraFactory::getInstance()

	//	trSession->addDestination(targetIp, targetPort);

	sender->setTransportSession(trSession);

	return sender;
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

