/*
 * sessionmanager.h
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_
#include "gsck.h"
#include "infraexceptions.h"
#include "policyengine.h"
#include <cc++/thread.h>
#include <string>
#include "jobmanager.h"
#include "connectionlistener.h"
#include "trpsession.h"
#include <iostream>

namespace infrastream {

class ReceiverManager {
	GenericReceiverSocket& receiver;
public:
	ReceiverManager(GenericReceiverSocket& receiver);

	void run();

	void endSession();
};

class SenderManager {
	GenericSenderSocket& sender;
public:
	SenderManager(GenericSenderSocket& sender);

	void run();

	void endSession();
};

class SessionManager: public ConnectionListener {



	template<class T> class ThreadManager: public ost::Thread {
		bool active;
		bool invalidstate;
		T* manager;
		timeout_t latency;
		std::string name;
	protected:
		void run() {
			while (active) {
				manager->run();
				Thread::sleep(latency);
			}
		}
	public:
		ThreadManager() :
			active(false), invalidstate(true) {
		}

		ThreadManager(std::string managerName, T* manager, timeout_t l = 0) :
			active(false), invalidstate(false), latency(l) {
			//this->setName(managerName.c_str());
			this->name = managerName;
			this->manager = manager;
		}

		bool enable() {
			log_info("Enabling thread session");
			if (invalidstate) {
				log_error("It's not possible enable the session");
				return false;
			}
			active = true;
			int ret = Thread::start();
			if (ret) {
				std::cout<<"Valor de retorno da thread: "<<ret<<std::endl;
				log_error("Error on start session: " + name);
				throw CannotCreateSessionException(
						"Error on start thread session");
			}
			return active;
		}

		bool disable() {
			log_info("Disabling thread session");
			if (invalidstate) {
				log_error("It's not possible disable the session");
				return false;
			}
			Thread::exit();
			manager->endSession();
			return true;
		}
	};


public:
	// for full-transmission it is both parameters isn't null
	SessionManager(GenericSenderSocket* sender,
			GenericReceiverSocket* receiver, PolicyEngine* engine)
			throw (CannotCreateSessionException);

	void setTransportSession(TransportSession* trSession);

	void onNewRemoteConnection(std::string remoteIp, int port) {
		log_debug("New connection: "+ remoteIp);
		startSession();
	}

	TransportSession* getTSession();

	virtual ~SessionManager();

	void startSession();

	void endSession();

private:

	PolicyEngine* engine;
	TransportSession* trSession;
	GenericSenderSocket* sender;
	GenericReceiverSocket* receiver;

	ReceiverManager* recv;
	SenderManager* send;


	ThreadManager<PolicyEngine> engineManager;
	ThreadManager<JobManager> jobManager;
	ThreadManager<ReceiverManager> receiverManager;
	ThreadManager<SenderManager> senderManager;

};
}
#endif /* SESSIONMANAGER_H_ */
