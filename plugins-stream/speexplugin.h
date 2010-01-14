/*
 * speexplugin.h
 *
 *  Created on: 11/01/2010
 *      Author: ivocalado
 */

#ifndef SPEEXPLUGIN_H_
#define SPEEXPLUGIN_H_

#include <plugins/pluginsfactory.h>
#include <string>

#include "plugindefinitions.h"
#include <map>
#include <speex/speex.h>
#include <speex/speex_types.h>

class SpeexPlugin : public PluginStreamIF {
	map<std::string, MessageType> constants;
	void initConstants();
	void* encoderPtr;
	void* decoderPtr;
public:
	SpeexPlugin();
	virtual ~SpeexPlugin();

	virtual std::string retrievePluginInformation(std::string info, std::string subInfo = "")
				throw (OperationNotSupportedException, OperationNotPerfomedException);

	virtual void adaptStream(std::string paramName, std::map<std::string,
			std::string> &params)
				throw (OperationNotPerfomedException);

	virtual const char* getName() const;
};

#endif /* SPEEXPLUGIN_H_ */
