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
	virtual void doNegotiate() = 0;
	// Adicionar metodos padrao para negociacao
	virtual void notifyAdaptation(std::string paramName, std::map<std::string,
			std::string>& params) = 0;
};
#endif /* PLUGIN_NEGOTIATION_H_ */
