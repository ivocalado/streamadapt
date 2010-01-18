/*
 * sessionmanager.cpp
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#include <sessionmanager.h>
#include <logger/logger.h>

namespace infrastream {

SessionManager::SessionManager(GenericSenderSocket* sender,
		GenericReceiverSocket* receiver, PolicyEngine* engine) throw (CannotCreateSessionException) {
	if(!sender && !receiver) {
		log_error("Invalid session creating");
		throw CannotCreateSessionException("At least one endpoint must be valid");
	}

	if(!engine) {
		log_error("Strange! It shouldn't happen");
		throw CannotCreateSessionException("The Policy engine MUST be valid");
	}


	this->sender = sender;
	this->receiver = receiver;
	this->engine = engine;
}

SessionManager::~SessionManager() {

}

void SessionManager::setTransportSession(
		TransportSession* trSession) {
	this->trSession = trSession;
	engine->addListener(trSession);
}

void SessionManager::endSession(){
	log_error("Implementar finalizacao de sessao");
}
}
