/*
 * gssck.h
 *
 *  Created on: 29/12/2009
 *      Author: ivocalado
 */

#ifndef GSSCK_H_
#define GSSCK_H_
#include <cc++/config.h>

using namespace std;
namespace infrastream {
class GenericSenderSocket {


public:

//	PolicyEngine& getEngine();
	GenericSenderSocket();
	virtual ~GenericSenderSocket();

//	TransportSession& getSession(); //Temporario




	/**
	 * Provides an interface for source provider.
	 * It could a wrapper to sound card or web can
	 */
	virtual int read(uint8* buffer, size_t bufferLen) = 0;

};

//This class MUST be overhindden
class GenericReceiverSocket {
public:

	GenericReceiverSocket();
	virtual ~GenericReceiverSocket();



	virtual void newEventData(uint8* buffer, size_t bufferLen) = 0;
};
}

#endif /* GSSCK_H_ */
