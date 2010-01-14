/*
 * infrafactory.h
 *
 *  Created on: 30/12/2009
 *      Author: ivocalado
 */

#ifndef INFRAFACTORY_H_
#define INFRAFACTORY_H_
#include "plugins/pluginsfactory.h"
#include "policy/policy.h"
#include "trpsession.h"
#include "infraexceptions.h"
#include "logger/logger.h"
#include "policyengine.h"
#include "plugins/pluginnegotiation.h"

#include <memory>
#include <string>

using namespace std;
using namespace AdaptationPolicy;
namespace infrastream {

class InfraFactory {
	InfraFactory();
	static InfraFactory* instance;

public:
	static InfraFactory* getInstance();

	PluginNegotiationPtrlIF* buildNegotiationSession();

	TransportSession* buildTransportSession(
			PluginNegotiationPtrlIF* negotiation, auto_ptr<
					PolicyConfigurationType> policyDesc, PolicyEngine& engine,
			string targetIP, int targetPort, string serverIp = "",
			int serverPort = 0) throw(CannotCreateSessionException,
			InvalidPolicyException);

	virtual ~InfraFactory();
};

}

#endif /* INFRAFACTORY_H_ */
