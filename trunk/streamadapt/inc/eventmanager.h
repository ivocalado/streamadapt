/*
 * eventmanager.h
 *
 *  Created on: 22/01/2010
 *      Author: ivocalado
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "event.h"
#include "eventtype.h"

namespace infrastream {
class EventManager{
public:
	virtual Event getLastEvent(EventType eventType) = 0;;
};
}
#endif /* EVENTMANAGER_H_ */
