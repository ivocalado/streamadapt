/*
 * helperfunction.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef HELPERFUNCTION_H_
#define HELPERFUNCTION_H_

#include "logger/logger.h"
#include <map>
#include <string>
#include "plugins/pluginnegotiation.h"

using namespace std;


/**
 * This function will be used as a helper to configure the plugin
 * in both setup and In-transmission phases.
 */
template<class AdaptDesc, class Plugin> void configurePlugin(AdaptDesc & property, Plugin& session, PluginNegotiationPtrlIF* notifier = 0) {

	map<string, string> properties;

	typename AdaptDesc::simpleproperty_const_iterator simpleIt(
			property.simpleproperty().begin());

	log_info("Configuring plugin:");
	for (; simpleIt != property.simpleproperty().end(); ++simpleIt) {
		log_info("key = " + simpleIt->key() + " \t| value = " + *simpleIt);
		properties[simpleIt->key()] = *simpleIt;
		session->adapt(simpleIt->key(), properties);
		if(notifier)
			notifier->notifyAdaptation(simpleIt->key(), properties);
		properties.clear();
	}

	typename AdaptDesc::complexproperty_const_iterator complexIt(
			property.complexproperty().begin());
	for (; complexIt != property.complexproperty().end(); ++complexIt) {
		typename AdaptDesc::complexproperty_type::sub_property_const_iterator sub(
				complexIt->sub_property().begin());
		properties.clear();
		for (; sub != complexIt->sub_property().end(); ++sub) {
			properties[simpleIt->key()] = *sub;
		}
		session->adapt(complexIt->key(), properties);
		if(notifier)
			notifier->notifyAdaptation(complexIt->key(), properties);
	}

	log_info("End plugin configuration\n\n");
}

#endif /* HELPERFUNCTION_H_ */
