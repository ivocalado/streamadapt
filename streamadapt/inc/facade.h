/*
 * facade.h
 *
 *  Created on: 28/12/2009
 *      Author: ivocalado
 */

#ifndef FACADE_H_
#define FACADE_H_

#include <string>
#include <map>
#include <memory>
#include "gsck.h"
#include "infraexceptions.h"
#include "policy/policy.h"
#include "logger/logger.h"
#include "sessionmanager.h"

using namespace std;
using namespace AdaptationPolicy;

namespace infrastream {
class Facade {
	static Facade* instance;
	Facade();
	Facade(const Facade&);
	Facade& operator=(Facade&);
	auto_ptr<PolicyConfigurationType> loadPolicy(string policyPath)
			throw(CannotLoadPolicyException);
	//PolicyEngine engine;

public:
	string getName() const;

	static Facade* getInstance();
	virtual ~Facade();

	SessionManager* createClientSession(string targetIp, int targetPort,
			GenericSenderSocket* sender, GenericReceiverSocket* listener,
			string pluginPath = "", map<string, string> * additionalParams = 0)
			throw(CannotCreateSessionException, CannotLoadPolicyException);

	SessionManager* createServerSession(string localIP, int localport,
			GenericSenderSocket* sender, GenericReceiverSocket* listener,
			string pluginPath = "", map<string, string> * additionalParams = 0)
			throw(CannotCreateSessionException, CannotLoadPolicyException);

};
}

#endif /* FACADE_H_ */
