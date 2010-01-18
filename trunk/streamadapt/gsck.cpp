/*
 * gssck.cpp
 *
 *  Created on: 29/12/2009
 *      Author: ivocalado
 */

#include <gsck.h>

namespace infrastream {

GenericSenderSocket::GenericSenderSocket() {

}

GenericSenderSocket::~GenericSenderSocket() {
}

//void GenericSenderSocket::setTransportSession(
//		TransportSession* trSession) {
//	this->trSession = trSession;
//	engine.addListener(trSession);
//}

void GenericSenderSocket::run() {

	//TODO IMPLEMENTAR METODO RUN
}


GenericReceiverSocket::GenericReceiverSocket() {}
GenericReceiverSocket::~GenericReceiverSocket(){}

}
