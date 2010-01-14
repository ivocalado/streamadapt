/*
 * event.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include "event.h"

namespace infrastream {
Event::~Event(){}

Event::Event(EventType _type, double _payload) :
	type(_type) {
	payload = _payload;
}

Event::Event():type("")
{}

EventType Event::getType() const {
	return type;
}

void Event::setPayload(double payload) {
	this->payload = payload;
}

double Event::getPayload() const {
	return payload;
}


bool Event::operator<(const Event& event) const {
	return type < event.type;
}

bool Event::operator==(const Event& event) const {
	return type == event.type;
}

bool Event::operator!=(const Event& event) const {
	return !(*this == event);
}

}
