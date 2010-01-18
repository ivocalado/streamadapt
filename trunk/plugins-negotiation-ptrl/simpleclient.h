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

class SimpleClient : public Thread, public TagHandler
{
public:

	SimpleClient(std::string username, std::string password, std::string host, int port/*, XMPPNegotiation* plugin*/);
	virtual ~SimpleClient();

	void login();
	void logout();
	void sendMessage(Tag* mss);

	virtual void handleTag( Tag *tag );
	void newHasSupportEvent( Tag* tag );
	void newIqEvent( Tag* tag );

	void run(void);

private:
	Client* mClient;
};
