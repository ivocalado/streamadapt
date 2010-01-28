/*
 * main.cpp
 *
 *  Created on: 14/07/2009
 *      Author: ivocalado
 */

#ifdef MAIN_CLIENT
#include<stdio.h>
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
		SessionManager* session = facade->createClientSession(ia, port,
				new RecordDevice, new PlaybackDevice,
				"/home/ivocalado/workspace/streamadapt/policies/instance1.xml",
				0);

		TransportSession* sender = session->getTSession();
		uint32 timestamp = tstamp ? tstamp : 0;
		//
		//
		//
		string s = sender->getSession()->retrievePluginInformation(
				"CurrentRTPClockRate");
		istringstream s1(s);
		uint16 tstampInc = 0;
		s1 >> tstampInc;
		tstampInc /= packetsPerSecond;
		uint32 period = 1000 / packetsPerSecond;
		TimerPort::setTimer(period);
		for (int i = 0; i < count; i++) {
			uint32 tmp = timestamp + i * tstampInc;
			sender->getSession()->sendData(tmp, data,
					strlen((char *) data) + 1, &b);
			Thread::sleep(TimerPort::getTimer());
			TimerPort::incTimer(period);
		}
		session->endSession();
	}

private:
	const uint16 packetsPerSecond;
};

#include <policy/policy.h>
#include <memory>
using namespace AdaptationPolicy;
using namespace std;

#include <string>

int main(int argc, char *argv[]) {

	//	auto_ptr<PolicyConfigurationType> policyDesc = adaptation_policy(
	//			"/home/ivocalado/workspace/streamadapt/policies/instance1.xml");
	//	string
	//			s =
	//					policyDesc->startup_config().stream().transmission_properties().transmission_type();
	//	cout<<"S: "<<s<<endl;

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
#endif
