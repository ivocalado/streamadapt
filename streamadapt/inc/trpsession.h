/*
 * trpsession.h
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#ifndef TRPSESSION_H_
#define TRPSESSION_H_

#include "policy/policy.h"
#include "plugins/pluginsfactory.h"
#include "session.h"
#include "policyengine.h"
#include "logger/logger.h"
#include "event.h"
#include "eventtype.h"
#include <memory>
#include <string>
#include <map>
#include "plugins/pluginnegotiation.h"

using namespace AdaptationPolicy;
using namespace std;
namespace infrastream {

class TransportSession: public Session {

	PolicyEngine* engine;

	adapt_config::transport_type* policy;
	auto_ptr<PluginTransportIF> session;
	//	bool enabledAdapt;

	map<EventType, const adapt_config::transport_type::policy_type*> dependencies;

	string transportProtocol;
	string pluginName;
	string libName;
public:
	TransportSession(string tProtocol, string pluginName, string libName,
			PolicyEngine* engine, PluginNegotiationPtrlIF* negotiation);

	void setPolicy(adapt_config::transport_type* policy)
			throw(InvalidPolicyException);

	void setTSession(auto_ptr<PluginTransportIF> tsession);

	auto_ptr<PluginTransportIF>& getSession();
	//	bool isEnabled() const;
	string getTransportProtocol() const;
	string getPluginName() const;
	string getLibName() const;



	void addDestination(string targetIp, int port);
	void sendData(uint32 stamp, const unsigned char* data = NULL, size_t len =
			0, ost::BaseAncillaryData* controlData = 0);
	const ost::AppDataUnit* readData();

	void endSession();

	string retrievePluginInformation(string key);


	virtual ~TransportSession();

	//-------------- session methods

	virtual void newEvent(Event event) throw(InvalidEventException);
	virtual set<EventType> getDependencies() throw(InvalidPolicyException);
};

}

#endif /* TRPSESSION_H_ */