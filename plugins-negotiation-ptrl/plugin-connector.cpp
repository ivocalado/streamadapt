/*
 * plugin-connector.cpp
 *
 *  Created on: 18/08/2009
 *      Author: ivocalado
 */

#include <string>
#include <plugins/pluginsfactory.h>

#include "xmppnegotiation.h"

using namespace std;
#define VERSION "0.1"
class NPluginFactory: public NegotiationPtrlPluginFactory {
public:

	NPluginFactory() :
		NegotiationPtrlPluginFactory(NEGOTIATION_PLUGIN) {
	}
	PluginNegotiationPtrlIF* create() {
		return new XMPPNegotiation;
	}
	std::string getName() {
		return "negotiation-plugin";
	}

	string getDescription() {
		return "This plugin makes negotiation action";
	}

	string getVersion() {
		return VERSION;
	}

};

extern "C" {
void registerPlugin(PluginManager &PM) {
	PM.registerNegotiationPtrlPluginFactory(new NPluginFactory);
}

}
