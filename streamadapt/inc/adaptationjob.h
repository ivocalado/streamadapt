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

#include <iostream>
namespace infrastream {

template<class AdaptDesc, class Plugin, class Notifier> class AdaptationJob: public infrastream::AbstractJob {
	AdaptDesc* property;
	Plugin& session;
	Notifier* notifier;
public:
	AdaptationJob(AdaptDesc*  _property, Plugin& _session,
			Notifier* notifier = 0) :
		session(_session) {
		property = _property;
	}
	virtual ~AdaptationJob() {
	}

	void executeJob() {
		map<string, string> properties;

		typename AdaptDesc::simpleproperty_const_iterator simpleIt(
				property->simpleproperty().begin());

		log_info("Configuring plugin:");
		for (; simpleIt != property->simpleproperty().end(); ++simpleIt) {
			log_info("Passou aqui 1");
			//std::cout<< "Key: "<<simpleIt->key()<<std::endl;
		//	if(simpleIt->key()) {
			//	std::cout<<"Not Nuloo"<<std::endl;
			//} else
				//std::cout<<"Nuloo"<<std::endl;
			//log_info("Passou aqui 1.1");
			//std::cout<< "Value: "<<*simpleIt<<std::endl;
			//*simpleIt;
			log_info("Passou aqui 1.2");
			//log_info("key = " + simpleIt->key() + " \t| value = "/* + *simpleIt*/);
			properties[simpleIt->key()] = *simpleIt;
			log_info("Passou aqui 2");
			try {
				log_info("Passou aqui 3");
				session->adapt(simpleIt->key(), properties);
				log_info("Passou aqui 4");
				if (notifier)
					notifier->notifyAdaptation(simpleIt->key(), properties);
				log_info("Passou aqui 5");
				properties.clear();
			} catch (...) {
				log_error("Problem in execute adaptation. Revise your policy");
			}
		}
		log_info("Passou aqui 6");
		typename AdaptDesc::complexproperty_const_iterator complexIt(
				property->complexproperty().begin());
		for (; complexIt != property->complexproperty().end(); ++complexIt) {
			typename AdaptDesc::complexproperty_type::sub_property_const_iterator
					sub(complexIt->sub_property().begin());

			try{
			properties.clear();
			for (; sub != complexIt->sub_property().end(); ++sub) {
				properties[simpleIt->key()] = *sub;
			}
			session->adapt(complexIt->key(), properties);
			if (notifier)
				notifier->notifyAdaptation(complexIt->key(), properties);
			} catch (...) {
				log_error("Problem in execute adaptation. Revise your policy");
			}
		}

		log_info("End plugin configuration\n\n");

	}
};

}

#endif /* ADAPTATIONJOB_H_ */
