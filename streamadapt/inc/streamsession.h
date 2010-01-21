/*
 * streamsession.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef STREAMSESSION_H_
#define STREAMSESSION_H_

#include "session.h"
#include "policyengine.h"
#include "policy/policy.h"
#include "plugins/pluginsfactory.h"
#include <memory>
#include <map>
#include "eventtype.h"
#include <string>

using namespace AdaptationPolicy;
using namespace std;

namespace infrastream {

class StreamSession: public infrastream::Session {
	PolicyEngine* engine;
	adapt_config::stream_type* policy;
	auto_ptr<PluginStreamIF> session;

	map<EventType, const adapt_config::stream_type::policy_type*> dependencies;


public:
	StreamSession(string pluginName, string libName,
			PolicyEngine* engine, PluginNegotiationPtrlIF* negotiation)
			throw(CannotCreateSessionException);

	void setSSession(auto_ptr<PluginStreamIF> tsession);

	void setPolicy(adapt_config::stream_type* policy)
			throw(InvalidPolicyException);



	auto_ptr<PluginStreamIF>& getSession();

	void endSession();

	virtual void newEvent(Event event) throw(InvalidEventException);
	virtual set<EventType> getDependencies() throw(InvalidPolicyException);

	virtual ~StreamSession();
};

}

#endif /* STREAMSESSION_H_ */
