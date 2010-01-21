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
#include "streamsession.h"

#include <memory>
#include <string>

using namespace std;
using namespace AdaptationPolicy;
namespace infrastream {

class InfraFactory {
	InfraFactory();
	static InfraFactory* instance;

public:
	enum SessionType {
		SERVER_SESSION, CLIENT_SESSION
	};

	static InfraFactory* getInstance();

	PluginNegotiationPtrlIF* buildNegotiationSession();

	TransportSession* buildTransportSession(
			PluginNegotiationPtrlIF* negotiation, auto_ptr<
					PolicyConfigurationType> policyDesc, PolicyEngine& engine,
			string ip, int port, InfraFactory::SessionType sessionType,
			ConnectionListener* listener = 0) throw(CannotCreateSessionException,
			InvalidPolicyException);

	StreamSession* buildStreamSession(PluginNegotiationPtrlIF* negotiation, auto_ptr<
			PolicyConfigurationType> policyDesc, PolicyEngine& engine) throw (CannotCreateSessionException,InvalidPolicyException);



	virtual ~InfraFactory();
};

}

#endif /* INFRAFACTORY_H_ */
