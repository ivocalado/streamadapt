/*
 * plugin_base.cpp
 *
 *  Created on: 19/12/2009
 *      Author: ivocalado
 */

#include <plugins/pluginbase.h>
#include <algorithm>

using namespace std;
size_t PluginBase::fireEvent(PluginSignal signal, void* objFired) {
	map<PluginSignal, set<PluginListener*> >::iterator it = listeners.find(
			signal);
	if (it == listeners.end())
		return 0;
	set<PluginListener*> firedListeners = it->second;
	for (set<PluginListener*>::iterator i = firedListeners.begin(); i
			!= firedListeners.end(); i++)
		(*i)->newEvent(objFired);
	return firedListeners.size(); //Number of listeners fired
}

void PluginBase::addListener(PluginSignal signal, PluginListener* listener)
		throw (OperationNotSupportedException) {
	if (!listener)
		throw OperationNotSupportedException("Invalid param");

	map<PluginSignal, set<PluginListener*> >::iterator it = listeners.find(
			signal);
	if (it == listeners.end()) {
		set<PluginListener*> l;
		l.insert(listener);
		listeners[signal] = l;
	} else {

		it->second.insert(listener);
	}
}

bool PluginBase::removeListener(PluginSignal signal,
		PluginListener* listenerToRemove) {
	map<PluginSignal, set<PluginListener*> >::iterator it = listeners.find(
			signal);
	if (it == listeners.end())
		return false;
	set<PluginListener*> l = it->second;
	set<PluginListener*>::iterator i = l.find(listenerToRemove);
	if (i == l.end())
		return false;
	l.erase(*i);
	return true;
}
