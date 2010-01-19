/*
 * adaptationjob.h
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#ifndef ADAPTATIONJOB_H_
#define ADAPTATIONJOB_H_

#include "abstractjob.h"

#include "logger/logger.h"
#include <map>
#include <string>
#include "plugins/pluginnegotiation.h"

namespace infrastream {

template<class AdaptDesc, class Plugin> class AdaptationJob: public infrastream::AbstractJob {
	AdaptDesc& property;
	Plugin& session;
	PluginNegotiationPtrlIF* notifier;
public:
	AdaptationJob(AdaptDesc & _property, Plugin& _session,
			PluginNegotiationPtrlIF* notifier = 0) :
		property(_property), session(_session) {
	}
	virtual ~AdaptationJob() {
	}

	void executeJob() {
		map<string, string> properties;

		typename AdaptDesc::simpleproperty_const_iterator simpleIt(
				property.simpleproperty().begin());

		log_info("Configuring plugin:");
		for (; simpleIt != property.simpleproperty().end(); ++simpleIt) {
			log_info("key = " + simpleIt->key() + " \t| value = " + *simpleIt);
			properties[simpleIt->key()] = *simpleIt;
			session->adapt(simpleIt->key(), properties);
			if (notifier)
				notifier->notifyAdaptation(simpleIt->key(), properties);
			properties.clear();
		}

		typename AdaptDesc::complexproperty_const_iterator complexIt(
				property.complexproperty().begin());
		for (; complexIt != property.complexproperty().end(); ++complexIt) {
			typename AdaptDesc::complexproperty_type::sub_property_const_iterator
					sub(complexIt->sub_property().begin());
			properties.clear();
			for (; sub != complexIt->sub_property().end(); ++sub) {
				properties[simpleIt->key()] = *sub;
			}
			session->adapt(complexIt->key(), properties);
			if (notifier)
				notifier->notifyAdaptation(complexIt->key(), properties);
		}

		log_info("End plugin configuration\n\n");

	}
};

}

#endif /* ADAPTATIONJOB_H_ */
