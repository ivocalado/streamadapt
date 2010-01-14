/*
 * gssck.cpp
 *
 *  Created on: 29/12/2009
 *      Author: ivocalado
 */

#include <gsck.h>

namespace infrastream {
PolicyEngine& GenericSenderSocket::getEngine() {
	return engine;
}

GenericSenderSocket::GenericSenderSocket() {

}

GenericSenderSocket::~GenericSenderSocket() {
	// TODO Auto-generated destructor stub
}

void GenericSenderSocket::setTransportSession(
		TransportSession* trSession) {
	this->trSession = trSession;
}

void GenericSenderSocket::run() {

	//TODO IMPLEMENTAR METODO RUN
}

void GenericSenderSocket::endSession() {
	trSession->endSession();
}

TransportSession& GenericSenderSocket::getSession() {
	return *trSession;
}

}
