/*
 * main.cpp
 *
 *  Created on: 14/07/2009
 *      Author: ivocalado
 */
#ifdef MAIN_SERVER
#include <iostream>
#include <facade.h>
#include <logger/logger.h>
#include <logger/consoleappender.h>
#include <trpsession.h>
using namespace std;
using namespace infrastream;

#include <gsck.h>
#include <sstream>
#include <cstdlib>
#include <cc++/thread.h>
#include <sessionmanager.h>
using namespace ost;

class RecordDevice: public GenericSenderSocket {
public:
	int read(uint8* buffer, size_t bufferLen) {
		return 0; // Le dados da sound card
	}
};

class PlaybackDevice: public GenericReceiverSocket {
public:
	void newEventData(uint8* buffer, size_t bufferLen) {
		//recebe dados para ser renderizado
	}

	virtual ~PlaybackDevice() {
	}
};
class Receiver {
	BaseAncillaryData b;
public:
	Receiver(string ia, tpport_t port) {

		Facade* facade = Facade::getInstance();
		SessionManager* session = facade->createServerSession(ia, port,
				new RecordDevice, new PlaybackDevice,
				"/home/ivocalado/workspace/streamadapt/policies/instance1.xml",
				0);

		TransportSession* sender = session->getTSession();

		for (;;) {
			const AppDataUnit* adu;
			while ( (adu = sender->readData()) ) {
				cerr << "I got an app. data unit - "
				<< adu->getSize()
				<< " payload octets ("
				<< "pt " << (int)adu->getType()
				<< ") from "
				<< hex << (int)adu->getSource().getID()
				<< "@" << dec <<
				adu->getSource().getNetworkAddress()
				<< ":"
				<< adu->getSource().getDataTransportPort()
				<< endl;
				cerr << "Dado: "<<adu->getData()<<endl;
				delete adu;
			}
			Thread::sleep(7);
		}
	}

};

int main(int argc, char *argv[]) {
	cout << "rtplisten" << endl;

	if (argc != 3) {
		cerr << "Syntax: " << " ip port" << endl;
		exit(1);
	}

	Receiver receiver(argv[1], atoi(argv[2]));


	return 0;
}

#endif
