/*
 * eventtype.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef EVENTTYPE_H_
#define EVENTTYPE_H_
#include <string>

using namespace std;

namespace infrastream {
class EventType {
	std::string name;
public:
	EventType(std::string name);
	virtual ~EventType();
	bool operator<(const EventType& type) const;
	bool operator==(const EventType& type) const;
	bool operator==(const std::string& name) const;
	std::string getName() const;
};

}
#endif /* EVENTTYPE_H_ */
