/*
 * DCCPSocketPlugin.cpp
 *
 *  Created on: 21/12/2009
 *      Author: ivocalado
 */

#include "dccpsocketplugin.h"
#include <sstream>
#include <ostream>
#include <logger/logger.h>

DCCPSocketPlugin::DCCPSocketPlugin() {
	rtpSession = 0;
}

DCCPSocketPlugin::~DCCPSocketPlugin() {
	// TODO Auto-generated destructor stub
}

void DCCPSocketPlugin::adaptTransport(string paramName, std::map<std::string,
		std::string> &params) throw (OperationNotPerfomedException,
		OperationNotSupportedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException("Session not built");
	if (params.size() == 0)
		throw OperationNotPerfomedException("Invalid parameter");

	if (paramName == EXPIRE_TIMEOUT) {
		istringstream str(params.begin()->second);
		microtimeout_t timeout;
		str >> timeout;
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid paramater value: timeout");
		rtpSession->setExpireTimeout(timeout);
	} else if (paramName == SCHEDULING_TIMEOUT) {
		istringstream str(params.begin()->second);
		microtimeout_t timeout;
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid paramater value: timeout");
		rtpSession->setSchedulingTimeout(timeout);
	} else if (paramName == SDESITEM) {
		defaultApplication().setSDESItem(SDESItemTypeTOOL,
				params.begin()->second);
	} else if (paramName == PAYLOAD_FORMAT) {
		int payload;
		istringstream str(params.begin()->second);
		str >> payload;
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid parameter value: payload");
		rtpSession->setPayloadFormat(StaticPayloadFormat(
				(StaticPayloadType) payload));
	} else if (paramName == DCCP_TX_CCID) {
		int ccid;
		istringstream str(params.begin()->second);
		str >> ccid;
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid parameter value: payload");

		try {
			rtpSession->getDSO()->setSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_CCID, &ccid);
		} catch (...) {
			//			throw;
			throw OperationNotPerfomedException("Invalid CCID");
		}

	} else if (paramName == DCCP_TX_QUEUELEN) {
		int len;
		istringstream str(params.begin()->second);
		str >> len;
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid parameter value: payload");

		try {
			rtpSession->getDSO()->setSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_QUEUELEN, &len);
		} catch (...) {
			throw OperationNotPerfomedException("Invalid Queue len");
		}

	} else if (paramName == DCCP_TX_POLICYID) {
		map<string, string>::const_iterator policyId = params.find("id");
		map<string, string>::const_iterator changeAction =
				params.find("action");
		if (policyId == params.end() || changeAction == params.end())
			throw OperationNotPerfomedException("Need more parameters");

		int p[2];
		istringstream str(policyId->second);
		str >> p[0];
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid parameter value: policyId");

		istringstream str2(changeAction->second);
		str >> p[1];
		if (str.fail())
			throw OperationNotPerfomedException(
					"Invalid parameter value: policyId");

		try {
			rtpSession->getDSO()->setSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_POLICYID, p);
		} catch (...) {
			throw OperationNotPerfomedException("Invalid Queue len");
		}
	} else {
		throw OperationNotSupportedException();
	}

}

void DCCPSocketPlugin::buildSession(std::string hostIp, int hostPort, infrastream::ConnectionListener* manager) throw(CannotBindSocketException,
		CannotCreateSocketException) {
	if (rtpSession)
		throw CannotCreateSocketException(
				"The session already exist. Please, end the current session before");
	try {
		InetHostAddress ia(hostIp.c_str());
		rtpSession = new RTPDCCPS(this, ia, hostPort);
	} catch (...) {
		if (rtpSession) {
			delete rtpSession;
			rtpSession = 0;
		}
		throw CannotBindSocketException();
	}

	this->listener = manager;
}

void DCCPSocketPlugin::addDestination(std::string target, int port)
		throw(CannotConnectSocketException) {
	if (!rtpSession)
		throw CannotConnectSocketException();
	rtpSession->setDestination(InetHostAddress(target.c_str()), port);
}

void DCCPSocketPlugin::endSession() throw(OperationNotPerfomedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException();
	try {
		delete rtpSession;
	} catch (...) {
		throw OperationNotPerfomedException("An error ocurried in end Session");
	}
	rtpSession = 0;
}

void DCCPSocketPlugin::sendData(uint32 stamp, const unsigned char* data,
		size_t len, ost::BaseAncillaryData* controlData)
		throw (OperationNotPerfomedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException();
	rtpSession->putData(stamp, data, len, controlData);
}

void DCCPSocketPlugin::sendImmediateData(uint32 stamp,
		const unsigned char* data, size_t len,
		ost::BaseAncillaryData* controlData)
		throw (OperationNotPerfomedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException();
	rtpSession->sendImmediate(stamp, data, len, controlData);
}

#include <stdio.h>
string DCCPSocketPlugin::retrievePluginInformation(std::string info,
		std::string /*subInfo*/) throw (OperationNotSupportedException,
		OperationNotPerfomedException) {
	log_info("DCCPSocketPlugin::retrievePluginInformation");
	if (!rtpSession)
		throw OperationNotPerfomedException();

	if (info == CURRENT_RTP_CLOCK_RATE) {
		ostringstream s;
		s << rtpSession->getCurrentRTPClockRate();
		return s.str();
	} else if (info == DCCP_TX_CCID) {
		int ccid;
		try {
			rtpSession->getDSO()->getSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_CCID, &ccid);
		} catch (...) {
			throw OperationNotPerfomedException("CCID not retrieved");
		}
		ostringstream ret;
		ret << ccid;
		return ret.str();
	} else if (info == DCCP_RX_CCID) {
		int ccid;
		try {
			rtpSession->getDSO()->getReceiverSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::RX_CCID, &ccid);
		} catch (...) {
			throw OperationNotPerfomedException("Invalid CCID");
		}
		ostringstream ret;
		ret << ccid;
		return ret.str();
	} else if (info == DCCP_TX_QUEUELEN) {
		int len;
		try {
			rtpSession->getDSO()->getSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_QUEUELEN, &len);
		} catch (...) {
			throw OperationNotPerfomedException("Invalid Queue len");
		}
		ostringstream ret;
		ret << len;
		return ret.str();

	} else if (info == DCCP_TX_POLICYID) {
		int policyId;
		try {
			rtpSession->getDSO()->getSenderSocketOption(
					rtpSession->targetAddress(), rtpSession->targetPort(),
					RTPBaseDCCPIPv4Socket::TX_POLICYID, &policyId);

		} catch (...) {
			throw OperationNotPerfomedException("Invalid Queue len");
		}
		ostringstream ret;
		ret << policyId;
		return ret.str();
	} else if (info == EXPIRE_TIMEOUT) {
		ostringstream ret;
		ret << rtpSession->getExpireTimeout();
		return ret.str();
	}
	throw OperationNotSupportedException();
}

const AppDataUnit* DCCPSocketPlugin::reatData(uint32* stamp)
		throw (OperationNotPerfomedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException();
	return rtpSession->getData(stamp ? *stamp : rtpSession->getFirstTimestamp());
}

void DCCPSocketPlugin::startSession() throw (OperationNotPerfomedException) {
	if (!rtpSession)
		throw OperationNotPerfomedException("Session not built");
	rtpSession->startRunning();
}

void DCCPSocketPlugin::newRemoteConnection(const InetHostAddress& remoteIp,
		int remotePort) {
	if (listener)
		this->listener->onNewRemoteConnection(remoteIp.getHostname(),
				remotePort);
}

void DCCPSocketPlugin::closeRemoteConnection() {
	if(listener)
		listener->onCloseRemoteConnection();
}
