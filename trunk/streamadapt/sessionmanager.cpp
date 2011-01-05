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
		GenericReceiverSocket* receiver, PolicyEngine* engine,
		PolicyConfigurationType* policy) throw (CannotCreateSessionException) {

	if (!policy) {
		log_error("Invalid session creating");
		throw CannotCreateSessionException(
				"The policy object cannot be null");
	}

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
	this->policy = policy;

	this->engineManagerThread = new ThreadManager<PolicyEngine> (
			"EngineManager", engine);
	this->jobManagerThread = new ThreadManager<JobManager> ("JobManager",
			JobManager::getInstance(), 500);

	if (this->sender) {
		senderManager = new SenderManager(*(this->sender));
		this->senderManagerThread = new ThreadManager<SenderManager> (
				"SenderManager", senderManager, 10000);
	} else {
		senderManagerThread = 0;
	}

	if (this->receiver) {
		receiverManager = new ReceiverManager(*(this->receiver));
		this->receiverManagerThread = new ThreadManager<ReceiverManager> (
				"ReceiverManager", receiverManager, 10000);
	} else
		receiverManagerThread = 0;

	trSession = 0;
	sSession = 0;

	activeManager = false;
}
void SessionManager::endSession() {
	log_info("Disabling sessions");
	if (jobManagerThread)
		jobManagerThread->disable();
	if (engineManagerThread)
		engineManagerThread->disable();

	if (receiverManagerThread)
		receiverManagerThread->disable();
	if (senderManagerThread)
		senderManagerThread->disable();

	try {
		if (trSession)
			trSession->endSession();
	} catch (...) {
		log_error("Exception in finalize Transport session. But we still continue");
	}

	try {
		if (sSession)
			sSession->endSession();
	} catch (...) {
		log_error("Exception in finalize Stream session. But we still continue");
	}

	activeManager = false;
}

SessionManager::~SessionManager() {
	if (activeManager) {
		log_info("Finalizing sessions");
		endSession();
	}

	if (receiverManager) {
		delete receiverManagerThread;
		delete receiverManager;
		log_info("Deleting receive manager thread");
		log_info("Deleting receive manager");
	}

	if (senderManager) {
		delete senderManagerThread;
		delete senderManager;
		log_info("Deleting send manager");
	}

	log_info("Deleting engine manager");
	delete engineManagerThread;

	log_info("Deleting Job Manager");
	delete jobManagerThread;

}

void SessionManager::setTransportSession(TransportSession* trSession) {
	this->trSession = trSession;
	engine->addListener(trSession);
}

void SessionManager::setStreamSession(StreamSession* sSession) {
	this->sSession = sSession;
	engine->addListener(sSession);
}

TransportSession* SessionManager::getTSession() {
	return this->trSession;
}

void SessionManager::startSession() {
	log_info("Starting managers session");
	if (jobManagerThread)
		jobManagerThread->enable();
	if (engineManagerThread)
		engineManagerThread->enable();
	if (receiverManagerThread)
		receiverManagerThread->enable();
	if (senderManagerThread)
		senderManagerThread->enable();
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
