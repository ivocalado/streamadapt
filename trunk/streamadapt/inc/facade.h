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
#include "policyengine.h"

using namespace std;
using namespace AdaptationPolicy;

namespace infrastream {
class Facade {
	static Facade* instance;
	Facade();
	Facade(const Facade&);
	Facade& operator=(Facade&);
	auto_ptr<PolicyConfigurationType> loadPolicy(string policyPath) throw(CannotLoadPolicyException);
	PolicyEngine engine;

public:
	string getName() const;

	static Facade* getInstance();
	virtual ~Facade();

	GenericSenderSocket* createSession(string localIP, int localport,
			string targetIp, int targetPort, string pluginPath = "",
			GenericReceiverSocket* listener = 0,
			map<string, string> * additionalParams = 0) throw(CannotCreateSessionException, CannotLoadPolicyException);

};
}


#endif /* FACADE_H_ */