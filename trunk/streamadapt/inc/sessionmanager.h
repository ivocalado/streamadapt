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
#include "streamsession.h"

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
			active(false), latency(l) {
			if (!manager)
				invalidstate = !manager;
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
				log_error("Error on start session: " + name);
				throw CannotCreateSessionException(
						"Error on start thread session: " + name);
			}
			return active;
		}

		bool disable() {
			log_info("Disabling thread session");
			if (invalidstate) {
				log_error("It's not possible disable the session");
				return false;
			}
			log_info("Disabling: " + name);
			exit();
			active = false;
			try {
				manager->endSession();
			} catch (...) {
				log_error("Error on finalize thread: " + name);
				return false;
			}
			return true;
		}
	};

public:
	// for full-transmission it is both parameters isn't null
	SessionManager(GenericSenderSocket* sender,
			GenericReceiverSocket* receiver, PolicyEngine* engine)
			throw (CannotCreateSessionException);

	void setTransportSession(TransportSession* trSession);

	void setStreamSession(StreamSession* sSession);

	void onNewRemoteConnection(std::string remoteIp, int port) {
		log_debug("New connection: "+ remoteIp);
		startSession();
	}

	TransportSession* getTSession();

	virtual ~SessionManager();

	void startSession();

	void endSession();

private:

	bool activeManager;
	PolicyEngine* engine;
	TransportSession* trSession;
	StreamSession* sSession;
	GenericSenderSocket* sender;
	GenericReceiverSocket* receiver;


	ReceiverManager* receiverManager;
	SenderManager* senderManager;

	ThreadManager<PolicyEngine>* engineManagerThread;
	ThreadManager<JobManager>* jobManagerThread;
	ThreadManager<ReceiverManager>* receiverManagerThread;
	ThreadManager<SenderManager>* senderManagerThread;

};
}
#endif /* SESSIONMANAGER_H_ */
