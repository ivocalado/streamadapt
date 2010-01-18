#include "simpleclient.h"
#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <stdio.h>
#include <iostream>
#include <gloox/stanza.h>

using namespace gloox;
using namespace std;

SimpleClient::SimpleClient(std::string username, std::string password,
		std::string host, int port/*, XMPPNegotiation* plugin*/) {
	JID jid(username);

	mClient = new Client(jid, password);
	mClient->setServer(host);
	mClient->setPort(port);

	mClient->registerTagHandler(this, MessageConstants::TAG_HAS_SUPPORT, MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	mClient->registerTagHandler(this, MessageConstants::TAG_IQ, MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
}

SimpleClient::~SimpleClient() {
	delete mClient;
}

void SimpleClient::login() {
	if (mClient->connect(false)) {
		ConnectionError ce = ConnNoError;
		while (ce == ConnNoError) {
			ce = mClient->recv();
		}
	}
}

void SimpleClient::run() {
	login();
}

void SimpleClient::logout() {
	mClient->disconnect();
}

void SimpleClient::sendMessage(Tag* mss) {
	mClient->send(mss);
}

void SimpleClient::handleTag(Tag *tag) {
	std::string nameTag = tag->name();
	if (nameTag == MessageConstants::TAG_HAS_SUPPORT)
		newHasSupportEvent(tag);
	else
		newIqEvent(tag);
}

void SimpleClient::newHasSupportEvent(Tag* tag) {
	printf("RECEBIDO UM HAS_SUPPORT_EVENT\n");
}

void SimpleClient::newIqEvent(Tag* tag) {
	std::string typeIq = tag->findAttribute(MessageConstants::IQ_ID_TYPE);
	if (atoi(typeIq.c_str()) == MessageConstants::RESULT)
		printf("RESULT\n");
	else if (atoi(typeIq.c_str()) == MessageConstants::RETRIVE)
		printf("RETRIVE\n");
	else
		printf("NOTIFY\n");
}
