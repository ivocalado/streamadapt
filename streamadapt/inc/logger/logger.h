/*
 * Logger.h
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <string>
#include <list>
#include "loggingappender.h"

using namespace std;

#ifdef DEBUG
#define USE_LOGGER
#endif

enum LogLevel {
	LOG_NONE, LOG_INFO, LOG_DEBUG, LOG_WARNING, LOG_ERROR
};

#ifdef USE_LOGGER
#define _log(str, level)	infralog::Logger::getInstance()->_log_msg(str, level);
#define setLogLevel(level) infralog::Logger::getInstance()->_setLevel(level);
#else
#define _log(str, level)
#define setLogLevel(level)
#endif

#define log_info(str) _log(str, LOG_INFO)
#define log_debug(str) _log(str, LOG_DEBUG)
#define log_warning(str) _log(str, LOG_WARNING)
#define log_error(str) _log(str, LOG_ERROR)

#ifdef USE_LOGGER
#define addAppender(appender)	infralog::Logger::getInstance()->_addAppender(appender);
//Verify if the two conditions are different and log it
#define checkAndLog(param1, param2, expect, msg, method) if((param1 == param2) == expect) method(msg);
#else
#define addAppender(appender)
#define checkAndLog(param1, param2, expect, msg, method)
#endif


#include <iostream>
using namespace std;
namespace infralog {
class Logger {
	LogLevel level;
	static Logger* instance;
	Logger();
	list<LoggingAppender*> appenders;

public:
	static Logger* getInstance();
	virtual ~Logger();
	inline void _setLevel(LogLevel l) {
		level = l;
	}

	LogLevel _getLevel() const {
		return level;
	}
	void _addAppender(LoggingAppender *appender);
	void _log_msg(string logMessage, LogLevel level);
};
}
#endif /* LOGGER_H_ */
