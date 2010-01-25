/*
 * sessionmanager.cpp
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#include <sessionmanager.h>
#include <logger/logger.h>
#include <iostream>
using namespace std;
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

	this->engineManager = new ThreadManager<PolicyEngine> ("EngineManager",
			engine);
	this->jobManager = new ThreadManager<JobManager> ("JobManager",
			JobManager::getInstance(), 50);

	if (this->sender) {
		send = new SenderManager(*(this->sender));
		this->senderManager = new ThreadManager<SenderManager> (
				"SenderManager", send);
	} else {
		senderManager = 0;
	}

	if (this->receiver) {
		recv = new ReceiverManager(*(this->receiver));
		this->receiverManager = new ThreadManager<ReceiverManager> (
				"ReceiverManager", recv);
	} else
		receiverManager = 0;

	//	t = Teste<A>(new A);
	//	t2 = Teste<B>(new B);
	//	t3 = Teste<C>(new C);
}

SessionManager::~SessionManager() {
	if (recv) {
		delete receiverManager;
		delete recv;
	}
	if (send) {
		delete senderManager;
		delete send;
	}
	delete engineManager;
	delete jobManager;
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
	if (jobManager)
		jobManager->enable();
	if (engineManager)
		engineManager->enable();
	if (receiverManager)
		receiverManager->enable();
	if (senderManager)
		senderManager->enable();
}

void SessionManager::endSession() {
	log_info("Destroying managers");
	if (jobManager)
		jobManager->disable();
	if (engineManager)
		engineManager->disable();

	if (receiverManager)
		receiverManager->disable();
	if (senderManager)
		senderManager->disable();
	//
	trSession->endSession();

}

ReceiverManager::ReceiverManager(GenericReceiverSocket& _receiver) :
	receiver(_receiver) {
}

void ReceiverManager::run() {
	//TODO IMPLEMENTAR RECEBIMENTO DE DADOS, NAO EH NECESSARIO COLOCAR WHILE(TRUE)
}

void ReceiverManager::endSession() {

}

SenderManager::SenderManager(GenericSenderSocket& _sender) :
	sender(_sender) {
}

void SenderManager::run() {
	//TODO IMPLEMENTAR THREAD DE ENVIO DE DADOS NAO EH NECESSARIO COLOCAR WHILE(TRUE)
}

void SenderManager::endSession() {
}

}
