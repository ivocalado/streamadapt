/*
 * adaptationmanager.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef ADAPTATIONMANAGER_H_
#define ADAPTATIONMANAGER_H_

#include <cc++/thread.h>
#include <stack>
#include <string>
#include <map>
#include "plugins/pluginbase.h"
#include "plugins/pluginnegotiation.h"
#include "plugins/streamexceptions.h"
#include <memory>

namespace infrastream {

/**
 * This class will be used to manage plugin adaptation. As an adaptation needs support
 * in remote side, a request is sent to negotiation side to verify if the chenge is
 * supported
 */
class AdaptationManager {
	std::auto_ptr<PluginNegotiationPtrlIF> negotiation;

public:
	AdaptationManager();
	virtual ~AdaptationManager();

	void commitAdaptation(PluginBase& plugin, std::string, std::map<
			std::string, std::string>& pMap)
			throw(OperationNotPerfomedException,
			OperationNotSupportedException);

};

}

#endif /* ADAPTATIONMANAGER_H_ */
