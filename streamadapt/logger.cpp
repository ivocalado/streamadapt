/*
 * Logger.cpp
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#include <logger/logger.h>

namespace infralog {

Logger* Logger::instance = 0;

Logger::Logger() :
	level(LOG_NONE) {

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

Logger* Logger::getInstance() {
	if (!instance)
		instance = new Logger;
	return instance;
}

void Logger::_addAppender(LoggingAppender *appender) {
	appenders.push_back(appender);
}

void Logger::_log_msg(string logMessage, LogLevel level) {
	if (this->level <= level && this->level != LOG_NONE) {
		switch (level) {
		case LOG_INFO:
			logMessage = "[INFO] " + logMessage;
			break;
		case LOG_DEBUG:
			logMessage = "[DEBUG] " + logMessage;
			break;
		case LOG_WARNING:
			logMessage = "[WARNING] " + logMessage;
			break;
		case LOG_ERROR:
			logMessage = "[ERROR] " + logMessage;
			break;
		default: break;
		};
		for (list<LoggingAppender*>::iterator it = appenders.begin(); it
				!= appenders.end(); it++)
			(*it)->newEventLog(logMessage);
	}
}
}
