/*
 * plugin_transport.h
 *
 *  Created on: 19/12/2009
 *      Author: ivocalado
 */

#ifndef PLUGIN_TRANSPORT_H_
#define PLUGIN_TRANSPORT_H_

#include <map>
#include <string>
#include "streamexceptions.h"
#include <ccrtp/rtp.h>
//#include <sessionmanager.h>
#include "pluginbase.h"
#include "connectionlistener.h"

const std::string DEFAULT_HOST_ADDRESS = "127.0.0.1";
const int DEFAULT_DATA_PORT = ost::DefaultRTPDataPort;

class PluginTransportIF : public PluginBase {

protected:
//	infrastream::SessionManager* manager;
	virtual void adaptTransport(
			std::string paramName, std::map<std::string, std::string> &params) throw (OperationNotPerfomedException, OperationNotSupportedException) = 0; // Adicionar metodos padrao para adaptacao a nivel de transporte
public:
	void adapt(std::string paramName, std::map<std::string, std::string>  &params)
			throw (OperationNotPerfomedException, OperationNotSupportedException) {
		adaptTransport(paramName, params);
	}
	virtual void buildSession(std::string target = DEFAULT_HOST_ADDRESS, int port = DEFAULT_DATA_PORT, infrastream::ConnectionListener* manager = 0)
			throw(CannotBindSocketException,
			CannotCreateSocketException) = 0;

	virtual void addDestination(std::string target, int port)
			throw(CannotConnectSocketException) = 0;

	virtual void startSession() throw(OperationNotPerfomedException) = 0;

	virtual void endSession() throw(OperationNotPerfomedException) = 0;

	virtual void sendData(uint32 stamp, const unsigned char* data = NULL,
			size_t len = 0, ost::BaseAncillaryData* controlData = 0)
			throw (OperationNotPerfomedException) = 0;

	virtual void sendImmediateData(uint32 stamp, const unsigned char* data = NULL,
			size_t len = 0, ost::BaseAncillaryData* controlData = 0)
			throw (OperationNotPerfomedException) = 0;

	virtual const ost::AppDataUnit* reatData(uint32* stamp = NULL) throw (OperationNotPerfomedException)= 0;

	virtual std::string
			retrievePluginInformation(std::string info, std::string subInfo = "")
					throw (OperationNotSupportedException, OperationNotPerfomedException) = 0;
	/*Each plugin has its own set of info constants*/
};

#endif /* PLUGIN_TRANSPORT_H_ */
