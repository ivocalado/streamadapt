/*
 * plugin-connector.cpp
 *
 *  Created on: 18/08/2009
 *      Author: ivocalado
 */

#include <plugins/pluginsfactory.h>
#include <memory>
#include "speexplugin.h"
#define VERSION "0.1"
class SPluginFactory: public StreamPluginFactory {
public:

	SPluginFactory() : StreamPluginFactory(STREAM_PLUGIN) {}
	PluginStreamIF* create() {
		return new SpeexPlugin;
	}

	std::string getName() {
		return "SpeexPlugin";
	}

	string getDescription() {
		return "This plugin makes stream adaptation";
	}

	string getVersion() {
		return VERSION;
	}

};

extern "C" {

void registerPlugin(PluginManager &PM) {
	//	std::auto_ptr<StreamAdaptorIF> ptr(new MyStreamAdaptor());
	PM.registerStreamPluginFactory(new SPluginFactory);
}

}
