/*
 * DCCPSocketPlugin.h
 *
 *  Created on: 21/12/2009
 *      Author: ivocalado
 */

#ifndef DCCPSOCKETPLUGIN_H_
#define DCCPSOCKETPLUGIN_H_

#include <plugins/plugintransport.h>
#include <plugins/streamexceptions.h>
#include <string>
#include <map>
#include <cstdlib>
#include <ccrtp/rtp.h>
#include <connectionlistener.h>
#include "plugindefinitions.h"

#ifdef  CCXX_NAMESPACES
using namespace ost;
using namespace std;
#endif

class DCCPSocketPlugin: public PluginTransportIF {
	infrastream::ConnectionListener* listener;

	class RTPDCCPS: public RTPDCCPSession {
		DCCPSocketPlugin* caller;
		InetHostAddress ia;
		tpport_t port;
		InetHostAddress remoteIa;
		tpport_t remotePort;
	public:

		RTPDCCPS(DCCPSocketPlugin* _caller, InetHostAddress& i, tpport_t pt) :
			RTPDCCPSession(i, pt), caller(_caller), ia(i), port(pt) {
		}
		// redefined from IncomingDataQueue
		void onNewSyncSource(const SyncSource& src) {
			cout << "* New synchronization source: " << hex
					<< (int) src.getID() << endl;

			remoteIa = InetHostAddress(src.getNetworkAddress().getHostname());
			remotePort = src.getDataTransportPort();
			addDestination(remoteIa, remotePort);

			caller->newRemoteConnection(remoteIa, remotePort);
		}

		// redefined from QueueRTCPManager
		void onGotSR(SyncSource& source, SendReport& SR, uint8 blocks) {
			RTPDCCPSession::onGotSR(source, SR, blocks);

			cout << "I got an SR RTCP report from " << hex
					<< (int) source.getID() << "@" << dec
					<< source.getNetworkAddress() << ":"
					<< source.getControlTransportPort() << endl;
		}

		// redefined from QueueRTCPManager
		void onGotRR(SyncSource& source, RecvReport& RR, uint8 blocks) {
			RTPDCCPSession::onGotRR(source, RR, blocks);
			//			RR.blocks[0].rinfo.
			cout << "I got an RR RTCP report from " << hex
					<< (int) source.getID() << "@" << dec
					<< source.getNetworkAddress() << ":"
					<< source.getControlTransportPort() << endl;

		}

		// redefined from QueueRTCPManager
		bool onGotSDESChunk(SyncSource& source, SDESChunk& chunk, size_t len) {
			bool result = RTPDCCPSession::onGotSDESChunk(source, chunk, len);
			cout << "I got a SDES chunk from " << hex << (int) source.getID()
					<< "@" << dec << source.getNetworkAddress() << ":"
					<< source.getControlTransportPort() << " ("
					<< source.getParticipant()->getSDESItem(SDESItemTypeCNAME)
					<< ") " << endl;

			return result;
		}

		void onGotGoodbye(const SyncSource& source, const std::string& reason) {
			cout << "I got a Goodbye packet from " << hex
					<< (int) source.getID() << "@" << dec
					<< source.getNetworkAddress() << ":"
					<< source.getControlTransportPort() << endl;
			cout << "   Goodbye reason: \"" << reason << "\"" << endl;
		}

		const InetHostAddress& targetAddress() const {
			return remoteIa;
		}

		tpport_t targetPort() const {
			return remotePort;
		}

		const InetHostAddress& hostAddress() const {
			return ia;
		}

		tpport_t hostPort() const {
			return port;
		}

		void setDestination(InetHostAddress addr, tpport_t pt) {
			remoteIa = addr;
			remotePort = pt;
			addDestination(addr, pt);
		}

	};

	RTPDCCPS* rtpSession;

public:
	DCCPSocketPlugin();
	virtual ~DCCPSocketPlugin();

	inline const char* getName() const {
		return PLUGIN_NAME;
	}

	void adaptTransport(std::string paramName, std::map<std::string,
			std::string> &params) throw (OperationNotPerfomedException,
			OperationNotSupportedException);

	void buildSession(infrastream::ConnectionListener* manager, string hostIp,
			int hostPort) throw(CannotBindSocketException,
			CannotCreateSocketException);

	void addDestination(string target, int port)
			throw(CannotConnectSocketException);

	void endSession() throw(OperationNotPerfomedException);

	void startSession() throw(OperationNotPerfomedException);

	void sendData(uint32 stamp, const unsigned char* data = NULL, size_t len =
			0, ost::BaseAncillaryData* controlData = 0)
			throw (OperationNotPerfomedException);

	void sendImmediateData(uint32 stamp, const unsigned char* data = NULL,
			size_t len = 0, ost::BaseAncillaryData* controlData = 0)
			throw (OperationNotPerfomedException);

	virtual const AppDataUnit* reatData(uint32* stamp = NULL)
			throw (OperationNotPerfomedException);

	string retrievePluginInformation(string info, std::string subInfo = "")
			throw (OperationNotSupportedException,
			OperationNotPerfomedException);

	void newRemoteConnection(const InetHostAddress& remoteIp, int remotePort);

};

#endif /* DCCPSOCKETPLUGIN_H_ */
