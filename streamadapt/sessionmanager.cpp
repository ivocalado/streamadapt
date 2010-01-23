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
		GenericReceiverSocket* receiver, PolicyEngine* engine)
		throw (CannotCreateSessionException) {
	if (!sender && !receiver) {
		log_error("Invalid session creating");
		throw CannotCreateSessionException(
				"At least one endpoint must be valid");
	}

	if (!engine) {
		log_error("Strange! It shouldn't happen");
		throw CannotCreateSessionException("The Policy engine MUST be valid");
	}

	this->sender = sender;
	this->receiver = receiver;
	this->engine = engine;

	this->engineManager = ThreadManager<PolicyEngine> ("EngineManager", engine);

	this->jobManager = ThreadManager<JobManager> ("JobManager",
			JobManager::getInstance(), 50);

	if(this->sender) {
		send = new SenderManager(*(this->sender));
		this->senderManager = ThreadManager<SenderManager>("SenderManager", send);
	}

	if(this->receiver) {
		recv = new ReceiverManager(*(this->receiver));
		this->receiverManager = ThreadManager<ReceiverManager>("ReceiverManager", recv);
	}
}

SessionManager::~SessionManager() {
	if(recv)
		delete recv;
	if(send)
		delete send;
}

void SessionManager::setTransportSession(TransportSession* trSession) {
	this->trSession = trSession;
	engine->addListener(trSession);
}

TransportSession* SessionManager::getTSession() {
	return this->trSession;
}

void SessionManager::startSession() {
	log_info("Starting managers session");
	jobManager.enable();
	engineManager.enable();
	receiverManager.enable();
	senderManager.enable();
}

void SessionManager::endSession() {
	log_info("Destroying managers");
	jobManager.disable();
	engineManager.disable();
	receiverManager.disable();
	senderManager.disable();

}

ReceiverManager::ReceiverManager(GenericReceiverSocket& _receiver) :
	receiver(_receiver) {
}

void ReceiverManager::run() {
	//TODO IMPLEMENTAR RECEBIMENTO DE DADOS, NAO EH NECESSARIO COLOCAR WHILE(TRUE)
}

void ReceiverManager::endSession() {}

SenderManager::SenderManager(GenericSenderSocket& _sender) :
	sender(_sender) {
}

void SenderManager::run() {
	//TODO IMPLEMENTAR THREAD DE ENVIO DE DADOS NAO EH NECESSARIO COLOCAR WHILE(TRUE)
}

void SenderManager::endSession(){}

}
