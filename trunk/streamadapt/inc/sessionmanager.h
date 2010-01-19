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


namespace infrastream {
class SessionManager {
	template<class T> class ThreadManager: public ost::Thread {
		bool active;
		bool invalidstate;
		T* manager;
		timeout_t latency;
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
			this->setName(managerName.c_str());
			this->manager = manager;
		}

		bool enable() {
			if (invalidstate)
				return false;
			active = true;
			if (Thread::start())
				throw CannotCreateSessionException(
						"Error on start thread session");
			return active;
		}

		bool disable() {
			if (invalidstate)
				false;
			Thread::exit();
			return true;
		}
	};

public:
	// for full-transmission it is both parameters isn't null
	SessionManager(GenericSenderSocket* sender,
			GenericReceiverSocket* receiver, PolicyEngine* engine)
			throw (CannotCreateSessionException);

	void setTransportSession(TransportSession* trSession);

	virtual ~SessionManager();

	void endSession();

private:

	PolicyEngine* engine;
	TransportSession* trSession;

	GenericSenderSocket* sender;
	GenericReceiverSocket* receiver;
	ThreadManager<PolicyEngine> engineManager;
	ThreadManager<JobManager> jobManager;
};
}
#endif /* SESSIONMANAGER_H_ */
