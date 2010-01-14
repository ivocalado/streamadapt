/*
 * plugin-connector.cpp
 *
 *  Created on: 18/08/2009
 *      Author: ivocalado
 */

#include <plugins/pluginsfactory.h>
#include <list>

using namespace std;
#define VERSION "0.1"
#include <plugins/plugintransport.h>
#include "dccpsocketplugin.h"

class TPluginFactory: public TransportPluginFactory {
public:

	TPluginFactory() :
		TransportPluginFactory(TRANSPORT_PLUGIN) {
	}
	PluginTransportIF* create() {
		return new DCCPSocketPlugin;
	}

	std::string getName() {
		return "DCCPSocketPlugin";
	}

	string getDescription() {
		return "This plugin makes transport adaptation";
	}

	string getVersion() {
		return VERSION;
	}

};

#include <stdio.h>


extern "C" {

void registerPlugin(PluginManager &PM) {
	PM.registerTransportPluginFactory(new TPluginFactory);
}
}
