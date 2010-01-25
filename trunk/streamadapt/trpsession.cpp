/*
 * trpsession.cpp
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#include <trpsession.h>
#include <logger/logger.h>

namespace infrastream {

TransportSession::TransportSession(string _tProtocol, string _pluginName,
		string _libName, PolicyEngine* engine,
		PluginNegotiationPtrlIF* _negotiation)
		throw(CannotCreateSessionException) :
	Session(_pluginName, _libName), transportProtocol(_tProtocol) {
	policy = 0;
	this->engine = engine;
	this->negotiation = negotiation;
}

TransportSession::~TransportSession() {
}

void TransportSession::setTSession(PluginTransportIF* tsession) {
	this->session = tsession;
}

void TransportSession::setPolicy(adapt_config::transport_type* _policy)
		throw(InvalidPolicyException) {
	if (!_policy) {
		log_error("Error on set policy in transport session");
		throw InvalidPolicyException("null policy object");
	}
	policy = _policy;
	adapt_config::transport_type::policy_const_iterator it(
			policy->policy().begin());
	map<EventType, const adapt_config::transport_type::policy_type*> eventsDep;
	for (; it != policy->policy().end(); ++it) {
		EventType newEvent(it->comparisson_attibute());
		if (eventsDep.find(newEvent) == eventsDep.end()) {
			eventsDep[newEvent] = &(*it);
		} else {
			log_debug("Invalid policy");
			InvalidPolicyException("Double definition of " + newEvent.getName());
		}
	}
	dependencies = eventsDep;
}

PluginTransportIF* TransportSession::getSession() {
	return this->session;
}

string TransportSession::getTransportProtocol() const {
	return this->transportProtocol;
}


void TransportSession::addDestination(string targetIp, int targetPort) {
	this->session->addDestination(targetIp, targetPort);

}

void TransportSession::sendData(uint32 stamp, const unsigned char* data,
		size_t len, ost::BaseAncillaryData* controlData) {
	session->sendData(stamp, data, len, controlData);

}

string TransportSession::retrievePluginInformation(string key) {
	return session->retrievePluginInformation(key);
}

const ost::AppDataUnit* TransportSession::readData(/*uint32* timestamp*/) {
	return session->reatData();
}

void TransportSession::endSession() {
	session->endSession();
}

void TransportSession::newEvent(Event event) throw(InvalidEventException) {
	log_info("TransportSession::newEvent");
	runInference(policy, *session, dependencies, engine, event, negotiation);
}

set<EventType> TransportSession::getDependencies()
		throw(InvalidPolicyException) {
	set<EventType> ret;
	for (map<EventType, const adapt_config::transport_type::policy_type*>::iterator
			it = dependencies.begin(); it != dependencies.end(); it++)
		ret.insert(it->first);
	return ret;
}

}
