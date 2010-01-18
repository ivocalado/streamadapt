/*
 * eventregister.cpp
 *
 *  Created on: 17/01/2010
 *      Author: ivocalado
 */

#include <eventregister.h>
#include <logger/logger.h>
namespace infrastream {

EventRegister::EventRegister(EventType event, timeout_t timestamp) :
	type(event), currentTimestamp(timestamp), defaultTimestamp(timestamp) {
	log_info("Creating EventRegister:");
	log_info("Eventype.getName(): "+ type.getName());

}

EventRegister::~EventRegister() {
	// TODO Auto-generated destructor stub
}

bool EventRegister::nextCicle(timeout_t t) {
	if (t <= 0) {
		t = 1;
		log_info("The timeout MUST be positive. Due to that, we will set it to 1 millisecond");
	}
	currentTimestamp -= t;
	if (currentTimestamp <= 0) {
		currentTimestamp = defaultTimestamp;
		log_info("throwing event: "+ this->type.getName());
		return true;
	}

	return false;
}

const EventType EventRegister::getEventType() const {
	return type;
}

}
