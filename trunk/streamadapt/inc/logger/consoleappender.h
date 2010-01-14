/*
 * consoleadaptor.h
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#ifndef CONSOLEAPPENDER_H_
#define CONSOLEAPPENDER_H_
#include <string>
#include "loggingappender.h"
#include "logger.h"
using namespace std;

namespace infralog {

class ConsoleAppender : public LoggingAppender {
public:
	ConsoleAppender();
	virtual ~ConsoleAppender();
	virtual void newEventLog(string message);
};

}

#endif /* CONSOLEADAPTOR_H_ */
