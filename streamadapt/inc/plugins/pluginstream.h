/*
 * plugin_stream.h
 *
 *  Created on: 19/12/2009
 *      Author: ivocalado
 */

#ifndef PLUGIN_STREAM_H_
#define PLUGIN_STREAM_H_
#include "pluginbase.h"
#include <map>
#include <string>

class PluginStreamIF: public PluginBase {
protected:
	virtual void adaptStream(std::string param, std::map<std::string, std::string> &params)
			throw (OperationNotPerfomedException) = 0; // Adicionar metodos padrao para adaptacao a nivel de stream
public:
	virtual void adapt(std::string param, std::map<std::string, std::string> &params)
			throw (OperationNotPerfomedException, OperationNotPerfomedException) {
		adaptStream(param, params);
	}

	virtual const char* getName() const = 0;

};

#endif /* PLUGIN_STREAM_H_ */
