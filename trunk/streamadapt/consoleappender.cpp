/*
 * consoleadaptor.cpp
 *
 *  Created on: 31/12/2009
 *      Author: ivocalado
 */

#include <logger/consoleappender.h>
#include <iostream>
using namespace std;
namespace infralog {

ConsoleAppender::ConsoleAppender() {
	// TODO Auto-generated constructor stub

}

ConsoleAppender::~ConsoleAppender() {
	// TODO Auto-generated destructor stub
}

void ConsoleAppender::newEventLog(string message) {
	cerr<<message<<endl;
}

}
