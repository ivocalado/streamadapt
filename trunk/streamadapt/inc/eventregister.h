/*
 * eventregister.h
 *
 *  Created on: 17/01/2010
 *      Author: ivocalado
 */

#ifndef EVENTREGISTER_H_
#define EVENTREGISTER_H_
#include <cc++/thread.h>
#include "eventtype.h"
namespace infrastream {

class EventRegister {
	timeout_t currentTimestamp;
	timeout_t defaultTimestamp;
	EventType type;
public:
	EventRegister(EventType type, timeout_t timestamp);
	bool nextCicle(timeout_t t);
	inline timeout_t getPeriod() const {
		return currentTimestamp;
	}

	virtual ~EventRegister();
	inline bool operator<(const EventRegister& r) const {
		return currentTimestamp < r.currentTimestamp;
	}

	const EventType getEventType() const;
};

}

#endif /* EVENTREGISTER_H_ */
