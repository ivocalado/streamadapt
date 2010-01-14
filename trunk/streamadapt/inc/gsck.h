/*
 * gssck.h
 *
 *  Created on: 29/12/2009
 *      Author: ivocalado
 */

#ifndef GSSCK_H_
#define GSSCK_H_
#include <cc++/config.h>
#include <cc++/thread.h>
#include <memory>
#include "trpsession.h"
#include "policyengine.h"

using namespace std;
namespace infrastream {
class GenericSenderSocket : ost::Thread {
	PolicyEngine engine;
	TransportSession* trSession;

protected:
	virtual void run();
public:
	PolicyEngine& getEngine();
	GenericSenderSocket();
	virtual ~GenericSenderSocket();
	void setTransportSession(TransportSession* trSession);
	TransportSession& getSession(); //Temporario

	void endSession();



};

//This class MUST be overhindden
class GenericReceiverSocket {
public:

	GenericReceiverSocket();
	virtual ~GenericReceiverSocket();



	virtual void newEventData(uint8* buffer, size_t bufferLen) = 0;
};
}
;
#endif /* GSSCK_H_ */
