/*
 * eventtype.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include "eventtype.h"
namespace infrastream {

EventType::EventType(string _name) :
	name(_name) {
}

EventType::~EventType() {}

bool EventType::operator<(const EventType& type) const {
	return name < type.name;
}

bool EventType::operator==(const EventType& type) const {
	return name == type.name;
}

bool EventType::operator==(const string& name) const {
	return this->name == name;
}

string EventType::getName() const {
	return name;
}


}
