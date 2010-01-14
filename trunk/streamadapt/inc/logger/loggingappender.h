/*
 * loggingappender.h
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#ifndef LOGGGING_APPENDER_H_
#define LOGGGING_APPENDER_H_
#include <string>

using namespace std;
namespace infralog {
class LoggingAppender {
public:
	LoggingAppender();
	virtual ~LoggingAppender();
	virtual void newEventLog(string message) = 0;
};
}
#endif /* LOGGGING_APPENDER_H_ */
