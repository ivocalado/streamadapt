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
#include "session.h"
#include "plugins/pluginbase.h"

using namespace std;

#define __default_value(x) "__default_" + x
namespace infrastream {

class PolicyEngine {

	map<EventType, set<Session*> > listeners;
	set<Event> currentValues;
	map<EventType, PluginBase*> providers;

public:

	/**
	 * Retrieve the last event from type @eventType
	 */
	Event getLastEvent(EventType eventType);

	void updateData();

	void registerProvider(EventType type, PluginBase* plugin,
			Event defaultEvent) throw(InvalidPolicyException);

	bool unregisterProvider(EventType type);

	void addListener(Session* listener);

	int fireEvent(Event event);

	PolicyEngine();
	virtual ~PolicyEngine();
};

}

#endif /* POLICYENGINE_H_ */
