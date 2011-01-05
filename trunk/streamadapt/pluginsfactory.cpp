/*
 * plugins-factory.cpp
 *
 *  Created on: 12/08/2009
 *      Author: ivocalado
 */

#include <plugins/pluginsfactory.h>
#include <logger/logger.h>

PluginManager* PluginManager::instance = 0;

PluginManager* PluginManager::getInstance() {
	if (!instance)
		instance = new PluginManager;
	return instance;
}

PluginManager::PluginManager() {
}

PluginManager::~PluginManager() {

	for (list<TransportPluginFactory*>::iterator i =
			transportPluginFactories.begin(); i
			!= transportPluginFactories.end(); i++)
		delete *i;

	for (list<NegotiationPtrlPluginFactory*>::iterator i =
			negotiatePluginFactories.begin(); i
			!= negotiatePluginFactories.end(); i++)
		delete *i;
	for (list<StreamPluginFactory*>::iterator i = streamPluginFactories.begin(); i
			!= streamPluginFactories.end(); i++)
		delete *i;
	for (list<void*>::iterator i = pluginHandlers.begin(); i
			!= pluginHandlers.end(); i++)
		dlclose(*i);
}


StreamPluginFactory* PluginManager::findStreamFactory(string name) {
	for (list<StreamPluginFactory*>::iterator i = streamPluginFactories.begin(); i
			!= streamPluginFactories.end(); i++)
		if ((*i)->getName() == name)
			return *i;
	return 0;
}

NegotiationPtrlPluginFactory* PluginManager::findNegotiationProtocolFactory(
		string name) {
	for (list<NegotiationPtrlPluginFactory*>::iterator i =
			negotiatePluginFactories.begin(); i
			!= negotiatePluginFactories.end(); i++)
		if ((*i)->getName() == name)
			return *i;
	return 0;
}

TransportPluginFactory* PluginManager::findTransportFactory(string name) {
	for (list<TransportPluginFactory*>::iterator i =
			transportPluginFactories.begin(); i
			!= transportPluginFactories.end(); i++)
		if ((*i)->getName() == name)
			return *i;
	return 0;
}



void PluginManager::loadPlugin(string pathName)
		throw(CannotLoadPluginException) {

	log_info("Lib Path: "+ pathName);

	void* plugin_h = 0;
	plugin_h = dlopen(pathName.c_str(), RTLD_NOW/*RTLD_LAZY*/);
	if (!plugin_h) {
		string error = "Cannot load plugin. Cause: ";
		error += dlerror();
		throw CannotLoadPluginException(error);
	}

	void (*loader)(PluginManager&) =
	(void(*)(PluginManager&))
	dlsym(plugin_h, DEFAULT_PLUGIN_LOAD_SYMBOL);


	if (!loader) {
		string error = "Cannot load plugin. Cause: ";
		error += dlerror();
		throw CannotLoadPluginException(error);
	}

	try {
		loader(*instance); //Loading plugin
	} catch (...) {
		log_error("Error in loading plugin!");
	}

	pluginHandlers.push_back(plugin_h);
	log_info("Plugin loaded");
}
