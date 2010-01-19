/*
 * connectionlistener.h
 *
 *  Created on: 19/01/2010
 *      Author: ivocalado
 */

#ifndef CONNECTIONLISTENER_H_
#define CONNECTIONLISTENER_H_

#include <string>

namespace infrastream {

class ConnectionListener {
public:
	ConnectionListener(){}
	virtual ~ConnectionListener(){}

	virtual void onNewRemoteConnection(std::string remoteIp, int port) = 0;
};

}

#endif /* CONNECTIONLISTENER_H_ */
