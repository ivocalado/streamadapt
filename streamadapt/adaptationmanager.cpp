/*
 * adaptationmanager.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include "inc/adaptationmanager.h"

namespace infrastream {

AdaptationManager::AdaptationManager() {
	// TODO Auto-generated constructor stub
}

AdaptationManager::~AdaptationManager() {
	// TODO Auto-generated destructor stub
}

void AdaptationManager::commitAdaptation(PluginBase& plugin,
		std::string paramName, std::map<std::string, std::string>& params)
		throw(OperationNotPerfomedException, OperationNotSupportedException) {

	plugin.adapt(paramName, params);
	negotiation->notifyAdaptation(paramName, params);
}

}
