/*
 * policyengine.h
 *
 *  Created on: 01/01/2010
 *      Author: ivocalado
 */

#ifndef POLICYENGINE_H_
#define POLICYENGINE_H_

#include <map>
#include <set>
#include <string>
#include <list>
#include <cc++/thread.h>

#include "session.h"
#include "plugins/pluginbase.h"
#include "eventregister.h"

using namespace std;
using namespace ost;
#define __default_value(x) "__default_" + x
namespace infrastream {

class PolicyEngine {

	map<EventType, set<Session*> > listeners; //will make glue with sessions
	set<Event> currentValues; // will keep current values
	map<EventType, PluginBase*> providers; // Will make the glue with the pluginBase
	list<EventRegister> registers; //Will keep registers to update


public:

	void run();
	/**
	 * Retrieve the last event from type @eventType
	 */
	Event getLastEvent(EventType eventType);

	void registerProvider(EventType type, unsigned int updateTime, PluginBase* plugin,
			Event defaultEvent) throw(InvalidPolicyException);

	bool unregisterProvider(EventType type);

	void addListener(Session* listener);

	int fireEvent(Event event);

	PolicyEngine();
	virtual ~PolicyEngine();
};

}

#endif /* POLICYENGINE_H_ */
