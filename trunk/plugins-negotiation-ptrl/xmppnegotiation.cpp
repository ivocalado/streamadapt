#include "xmppnegotiation.h"

#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/tag.h>
#include <stdio.h>
#include <iostream>
#include <gloox/stanza.h>

using namespace gloox;
using namespace std;

SimpleClient::SimpleClient(std::string username, std::string password,
		XMPPNegotiation* plugin, std::string host, int port) {

	xmppNegotiation = plugin;
	JID jid(username);

	mClient = new Client(jid, password);
	mClient->setServer(host);
	mClient->setPort(port);

	mClient->registerTagHandler(this, MessageConstants::IQ_NOTIFY,
			MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	mClient->registerTagHandler(this, MessageConstants::IQ_NOTIFY_RESPONSE,
			MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	mClient->registerTagHandler(this, MessageConstants::IQ_RETRIEVE,
			MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	mClient->registerTagHandler(this, MessageConstants::IQ_RETRIEVE_RESPONSE,
			MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
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

map<std::string, std::string> SimpleClient::getAttibutesTag(Tag* tag) {
	list<Tag::Attribute*> listAttr = tag->attributes();
	map<std::string, std::string> mapAttr;
	for (list<Tag::Attribute*>::iterator it = listAttr.begin(); it
			!= listAttr.end(); it++)
		mapAttr[(*it)->name()] = (*it)->value();
	return mapAttr;
}

void SimpleClient::handleTag(Tag *tag) {
	std::string message = tag->name();
	std::string messageType =
			tag->findAttribute(MessageConstants::MESSAGE_TYPE);
	if (message == MessageConstants::IQ_NOTIFY)
		xmppNegotiation->receivedIqNotify(getAttibutesTag(tag), messageType);
	else if (message == MessageConstants::IQ_NOTIFY_RESPONSE)
		xmppNegotiation->receivedIqNotifyRespose(getAttibutesTag(tag),
				messageType);
	else if (message == MessageConstants::IQ_RETRIEVE)
		xmppNegotiation->receivedIqRetrieve(tag->findAttribute(
				MessageConstants::ATTIBUTE_REQUIRED), messageType);
	else
		xmppNegotiation->receivedIqRetrieveResponse(tag->findAttribute(
				MessageConstants::ATTIBUTE_REQUIRED), tag->findAttribute(
				MessageConstants::ATTIBUTE_VALUE), messageType);
}

/*
 void SimpleClient::newHasSupportEvent(Tag* tag) {
 list<Tag::Attribute*> listAttr = tag->attributes();
 map<std::string, std::string> mapAttr;
 for (list<Tag::Attribute*>::iterator it = listAttr.begin(); it
 != listAttr.end(); it++)
 mapAttr[(*it)->name()] = (*it)->value();
 xmppNegotiation->updateAttrHasSuport(mapAttr);
 }
 */

//Class XMPPNegotiation
XMPPNegotiation::XMPPNegotiation() {
}

XMPPNegotiation::~XMPPNegotiation() {
	delete client;
	delete server;
}

void XMPPNegotiation::receivedIqNotify(
		map<std::string, std::string> attributes, std::string messageType) {

}

void XMPPNegotiation::receivedIqNotifyRespose(
		map<std::string, std::string> attributes, std::string messageType) {

}

void XMPPNegotiation::receivedIqRetrieve(std::string attribute,
		std::string messageType) {

}

void XMPPNegotiation::receivedIqRetrieveResponse(std::string attribute,
		std::string value, std::string messageType) {

}

void XMPPNegotiation::initNegotiation(std::string localIp, int localPort,
		std::string remoteIp, int remotePort,
		std::map<std::string, std::string>* params)
		throw (OperationNotPerfomedException) {
	if ((*params)["server"] == "yes") {
		isServer = true;
		server = new SimpleServer();
		client = new SimpleClient("client_local@boom", "", this);
	} else
		client = new SimpleClient("client_remote@boom", "", this, remoteIp,
				remotePort);

	if (isServer)
		server->start();
	client->start();
}

void XMPPNegotiation::shutdownNegotiation() {
	//server->stop();
	client->logout();
}

void XMPPNegotiation::notifyAdaptation(std::string paramName, std::map<
		std::string, std::string>& params) {
}

const char* XMPPNegotiation::getName() const {
	return name;
}

std::string XMPPNegotiation::retrievePluginInformation(std::string info,
		std::string subInfo) throw (OperationNotSupportedException) {

}
