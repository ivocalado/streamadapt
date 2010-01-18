#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/taghandler.h>
#include <gloox/iqhandler.h>
#include <stdio.h>
#include <iostream>
#include "message.h"
//#include "xmppnegotiation.h"
#include <cc++/thread.h>

using namespace gloox;
using namespace std;
using namespace ost;

class XMPPNegotiation;

class SimpleClient: public Thread, public TagHandler {

private:
	XMPPNegotiation* xmppNegotiation;

public:

	SimpleClient(std::string username, std::string password,
			XMPPNegotiation* plugin, std::string host = "localhost", int port =
					5222);
	virtual ~SimpleClient();

	void login();
	void logout();
	void sendMessage(Tag* mss);

	virtual void handleTag(Tag *tag);
	void newHasSupportEvent(Tag* tag);
	void newIqEvent(Tag* tag);

	void run(void);

private:
	Client* mClient;
};

#ifndef XMPPNEGOTIATION_H_
#define XMPPNEGOTIATION_H_

#include <plugins/pluginnegotiation.h>
#include <infraexceptions.h>
#include "simpleserver.h"
//#include "simpleclient.h"

#include <string>
#include <map>

class XMPPNegotiation: public PluginNegotiationPtrlIF {

private:
	bool isServer;
	SimpleClient* client;
	SimpleServer* server;

public:
	XMPPNegotiation();
	virtual ~XMPPNegotiation();

	virtual void initNegotiation(std::string localIp, int localPort,
			std::string remoteIp, int remotePort, std::map<std::string,
					std::string>* params = 0) throw (OperationNotPerfomedException);
	virtual void shutdownNegotiation();

	virtual void notifyAdaptation(std::string paramName, std::map<std::string,
			std::string>& params);
	virtual const char* getName() const;
	virtual std::string retrievePluginInformation(std::string info,
			std::string subInfo = "") throw (OperationNotSupportedException);

};
#endif /* XMPPNEGOTIATION_H_ */
