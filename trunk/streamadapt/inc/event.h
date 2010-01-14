/*
 * event.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "eventtype.h"

namespace infrastream {
class Event {
	EventType type;
	double payload;
public:
	virtual ~Event();

	bool operator<(const Event& event) const;
	bool operator==(const Event& event) const;
	bool operator!=(const Event& event) const;

	Event(EventType type, double payload = 0.0);
	Event();
	EventType getType() const;
	void setPayload(double payload);
	double getPayload() const;
};


}

#endif /* EVENT_H_ */
