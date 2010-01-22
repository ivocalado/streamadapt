/*
 * streamsession.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include <streamsession.h>
#include <logger/logger.h>

namespace infrastream {

StreamSession::StreamSession(string _pluginName, string _libName,
		PolicyEngine* engine, PluginNegotiationPtrlIF* negotiation)
		throw(CannotCreateSessionException) :
	Session(_pluginName, _libName) {
	policy = 0;
	this->engine = engine;
	this->negotiation = negotiation; // Testar negociacao
}

void StreamSession::setSSession(auto_ptr<PluginStreamIF> ssession) {
	this->session = ssession;
}

void StreamSession::setPolicy(adapt_config::stream_type* _policy)
		throw(InvalidPolicyException) {
	if (!_policy) {
		log_error("Error on set policy in stream session");
		throw InvalidPolicyException("null policy object");
	}
	policy = _policy;

	adapt_config::stream_type::policy_const_iterator it(
			policy->policy().begin());
	map<EventType, const adapt_config::stream_type::policy_type*> eventsDep;
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

auto_ptr<PluginStreamIF>& StreamSession::getSession() {
	return this->session;
}

void StreamSession::endSession() {
	//TODO finalizar sessao
}

void StreamSession::newEvent(Event event) throw(InvalidEventException) {
	log_info("StreamSession::newEvent");
	runInference(policy, session, dependencies, engine, event, negotiation);
}
set<EventType> StreamSession::getDependencies() throw(InvalidPolicyException) {
	set<EventType> ret;
	for (map<EventType, const adapt_config::stream_type::policy_type*>::iterator
			it = dependencies.begin(); it != dependencies.end(); it++)
		ret.insert(it->first);
	return ret;

}

string StreamSession::retrievePluginInformation(string key) {}


StreamSession::~StreamSession() {

}

}
