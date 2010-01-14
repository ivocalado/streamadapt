/*
 * factory.h
 *
 *  Created on: 12/08/2009
 *      Author: ivocalado
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "pluginbase.h"
#include "pluginstream.h"
#include "plugintransport.h"
#include "pluginnegotiation.h"
#include <logger/logger.h>


#include <string>
#include <memory>
#include <list>
#include <dlfcn.h>
#include <map>
#include <iostream>
#include <typeinfo>

#define DEFAULT_PLUGIN_LOAD_SYMBOL "registerPlugin" // this symbol will be used to load plugins
using namespace std;
#include "streamexceptions.h"

template<class Plugin> class Factory {
public:
	const PluginType type;
	virtual Plugin *create() = 0;
	virtual std::string getName() = 0;
	virtual std::string getVersion() = 0;
	virtual std::string getDescription() = 0;

	Factory(PluginType tp) :
		type(tp) {
	}

};

// Abstract Factories to instatiate plugins
typedef Factory<PluginStreamIF> StreamPluginFactory;
typedef Factory<PluginTransportIF> TransportPluginFactory;
typedef Factory<PluginNegotiationPtrlIF> NegotiationPtrlPluginFactory;

class PluginManager {

	static PluginManager* instance;

	list<StreamPluginFactory*> streamPluginFactories;
	list<TransportPluginFactory*> transportPluginFactories;
	list<NegotiationPtrlPluginFactory*> negotiatePluginFactories;

	list<void*> pluginHandlers;

	PluginManager();

public:

	static PluginManager* getInstance();

	// The definition here is needed to avoid undefined symbol error in plugin loading
	void registerTransportPluginFactory(TransportPluginFactory* plugin) {
		log_info("Registering transport factory: "+ plugin->getName());
		transportPluginFactories.push_back(plugin);
	}

	// The definition here is needed to avoid undefined symbol error in plugin loading
	void registerNegotiationPtrlPluginFactory(
			NegotiationPtrlPluginFactory* plugin) {
		log_info("Registering negotiation factory: "+ plugin->getName());
		negotiatePluginFactories.push_back(plugin);
	}

	// The definition here is needed to avoid undefined symbol error in plugin loading
	void registerStreamPluginFactory(StreamPluginFactory* plugin) {
		log_info("Registering stream factory: "+ plugin->getName());
		streamPluginFactories.push_back(plugin);
	}

	StreamPluginFactory* findStreamFactory(string name);

	NegotiationPtrlPluginFactory* findNegotiationProtocolFactory(string name);

	TransportPluginFactory* findTransportFactory(string name);

	template<class T> auto_ptr<T> findAdaptor(string pluginName,
			string fileName = "", string dirName = DEFAULT_PLUGINS_DIRECTORY)
			throw(CannotLoadPluginException) {
		Factory<T>* factory = findFactory<T> (pluginName);

		if (!factory) {
			if (fileName == "")
				fileName = pluginName;
			string pathName = dirName + fileName;
			loadPlugin(pathName); // Can throw an exception. Trying to load the plugin
			factory = findFactory<T> (pluginName);
			if (!factory)
				throw CannotLoadPluginException("Plugin unavailable");
		}

		return auto_ptr<T> ((T*) factory->create());
	}

	template<class T> void unregisterPlugin(string pluginName) {
		Factory<T>* factory = findFactory<T> (pluginName);
		if (!factory)
			throw CannotLoadPluginException("Plugin unavailable");

		PluginType type = factory->type;

		switch (type) {
		case STREAM_PLUGIN:
			streamPluginFactories.remove((StreamPluginFactory*) factory);
			break;
		case TRANSPORT_PLUGIN:
			transportPluginFactories.remove((TransportPluginFactory*) factory);
			break;
		case NEGOTIATION_PLUGIN:
			negotiatePluginFactories.remove(
					(NegotiationPtrlPluginFactory*) factory);
			break;
		default:
			throw CannotLoadPluginException("Plugin type unknown");
		};
		delete factory;
	}

	virtual ~PluginManager();

private:

	template<class T> Factory<T>* findFactory(string pluginName) {
		const type_info *t = &typeid(T);
		if (*t == typeid(PluginStreamIF))
			return dynamic_cast<Factory<T> *> (findStreamFactory(pluginName));
		else if (*t == typeid(PluginTransportIF))
			return dynamic_cast<Factory<T> *> (findTransportFactory(pluginName));
		else if (*t == typeid(PluginNegotiationPtrlIF))
			return dynamic_cast<Factory<T> *> (findNegotiationProtocolFactory(
					pluginName));
		else
			throw CannotLoadPluginException("Plugin type unknown");
	}

	void loadPlugin(string pathName) throw(CannotLoadPluginException);
};
#endif /* FACTORY_H_ */
