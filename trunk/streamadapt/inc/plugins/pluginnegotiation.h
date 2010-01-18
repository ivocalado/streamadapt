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

class PluginNegotiationPtrlIF: public PluginBase {
public:
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
