/*
 * plugin_base.h
 *
 *  Created on: 19/12/2009
 *      Author: ivocalado
 */

#ifndef PLUGIN_BASE_H_
#define PLUGIN_BASE_H_
#include <string>
#include <map>
#include <set>
#include "streamexceptions.h"

static std::string DEFAULT_PLUGINS_DIRECTORY= "./plugins/";

enum PluginType {
	STREAM_PLUGIN = 1, TRANSPORT_PLUGIN, NEGOTIATION_PLUGIN
};

typedef int PluginSignal;

class PluginListener {
public:
	virtual void newEvent(void*) = 0;
};

class PluginBase {
	std::map<PluginSignal, std::set<PluginListener*> > listeners;
protected:
	virtual inline void initPluginExec() {
	}

	virtual inline void shutdownPluginExec() throw (OperationNotPerfomedException){
	}

	size_t fireEvent(PluginSignal signal, void* obj);

public:
	virtual const char* getName() const = 0;

	virtual ~PluginBase() {
		shutdownPluginExec();
	}
	// Should be used in adaptation events
	virtual void adapt(std::string param, std::map<std::string, std::string> &params)
			throw(OperationNotPerfomedException, OperationNotSupportedException) {
	}

//	virtual void adaptRemote()

	/*MUST BE OVERHINDEN*/
	void addListener(PluginSignal signal, PluginListener* listener)
			throw (OperationNotSupportedException);
	bool removeListener(PluginSignal signal, PluginListener* listener);

	virtual std::string
				retrievePluginInformation(std::string info, std::string subInfo = "")
						throw (OperationNotSupportedException, OperationNotPerfomedException) = 0;

};

#endif /* PLUGIN_BASE_H_ */
