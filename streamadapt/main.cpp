/*
 * main.cpp
 *
 *  Created on: 14/07/2009
 *      Author: ivocalado
 */

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
class Sender: public TimerPort {
	BaseAncillaryData b;
public:
	Sender(const unsigned char* data, string ia, tpport_t port, uint32 tstamp,
			uint16 count) :

		packetsPerSecond(10) {

		Facade* facade = Facade::getInstance();

		SessionManager* sender = facade->createClientSession(ia, port,
				new RecordDevice, new PlaybackDevice,
				"/home/ivocalado/workspace/streamadapt/policies/instance1.xml",
				0);

		//		uint32 timestamp = tstamp ? tstamp : 0;
		//
		//
		//
		//		string s = sender->getSession().retrievePluginInformation(
		//				"CurrentRTPClockRate");
		//
		////		log_error("Passou aqui 2!");
		//
		//		//		cout<<"Passou aqui 4"<<endl;
		//		istringstream s1(s);
		//		uint16 tstampInc = 0;
		//		s1 >> tstampInc;
		//		tstampInc /= packetsPerSecond;
		//
		//		//		uint16 tstampInc = getCurrentRTPClockRate() / packetsPerSecond;
		//		uint32 period = 1000 / packetsPerSecond;
		//		//		cout<<"Passou aqui 5"<<endl;
		//		TimerPort::setTimer(period);
		//
		////		cout << "Passou aqui 6" << endl;
		//		for (int i = 0; i < count; i++) {
		//			uint32 tmp = timestamp + i * tstampInc;
		//			sender->getSession().sendData(tmp, data,
		//					strlen((char *) data) + 1, &b);
		//			//			cout<<"Passou aqui 7"<<endl;
		//			Thread::sleep(TimerPort::getTimer());
		//			TimerPort::incTimer(period);
		//			//			b.priority++;
		//		}
		//
		////		log_error("Passou aqui 1!");
		////		string s2 = sender->getSession()->retrievePluginInformation(
		////				"DCCPTXCCID");
		////		cout << "ccid: " << s2 << endl;

		sender->endSession();
	}

private:
	const uint16 packetsPerSecond;
};

int main(int argc, char *argv[]) {
	cout << "rtpsend..." << endl;

	if (argc != 6) {
		cerr << "Syntax: " << "data host port timestamp count" << endl;
		exit(1);
	}

	Sender sender((unsigned char *) argv[1], argv[2], atoi(argv[3]), atoi(
			argv[4]), atoi(argv[5]));

	cout << "I have sent " << argv[5] << " RTP packets containing \""
			<< argv[1] << "\", with timestamp " << argv[4] << " to " << argv[2]
			<< ":" << argv[3] << endl;
	return 0;
}
