/*
 * plugin_negotiation.h
 *
 *  Created on: 19/12/2009
 *      Author: ivocalado
 */

#ifndef PLUGIN_NEGOTIATION_H_
#define PLUGIN_NEGOTIATION_H_
#include "pluginbase.h"
#include <string>
#include <map>
#include <event.h>
#include <eventtype.h>
#include <policyengine.h>

class PluginNegotiationPtrlIF: public PluginBase {
	infrastream::PolicyEngine *engine;
protected:
	infrastream::Event retrieveLastLocalEvent(infrastream::EventType type) {
		return engine->getLastEvent(type);
	}
public:

	/**
	 * Differently from the others plugins, the negotiation needs to make a
	 * plugin-core talk
	 */
	void setEngine(infrastream::PolicyEngine *engine) {
		this->engine = engine;
	}

	virtual const char* getName() const = 0;
	// Adicionar metodos padrao para negociacao
	virtual void notifyAdaptation(std::string paramName, std::map<std::string,
			std::string>& params) = 0;

	virtual void initNegotiation(std::string localIp, int localPort,
			std::string remoteIp, int remotePort, std::map<std::string,
					std::string>* params = 0)
			throw (OperationNotPerfomedException) = 0;
	virtual void shutdownNegotiation() = 0;
};
#endif /* PLUGIN_NEGOTIATION_H_ */
