#include "xmppnegotiation.h"

XMPPNegotiation::XMPPNegotiation() {

}

XMPPNegotiation::~XMPPNegotiation() {
	delete client;
	//delete server;
}

void XMPPNegotiation::initNegotiation(std::string localIp, int localPort,
		std::string remoteIp, int remotePort,
		std::map<std::string, std::string>* params)
		throw (OperationNotPerfomedException) {
	if ((*params)["server"] == "yes") {
		isServer = true;
		//server = new SimpleServer();
		client = new SimpleClient("client_local@boom", "", this);
	} else
		client = new SimpleClient("client_remote@boom", "", this, remoteIp,
				remotePort);

	if (isServer)
		//server->start();
		client->start();
}

void XMPPNegotiation::shutdownNegotiation() {
	//server->stop();
	client->logout();
}

void XMPPNegotiation::updateAttrHasSuport(map<std::string, std::string> attr) {
	attHasSuport = attr;
}

map<std::string, std::string> XMPPNegotiation::getAttrHasSuport() {
	return attHasSuport;
}

void XMPPNegotiation::addPluginListener(PluginBase* plugin, list<std::string> attributes) {
	pluginsListeners[plugin] = attributes;
}

void XMPPNegotiation::removePluginListener(const char* namePlugin) {
	for(map<PluginBase*, list<std::string> >::iterator it = pluginsListeners.begin() ; it != pluginsListeners.end(); it++) {
		//TODO VERFICAR ESSA PARTE QUE FAZ ACESSO AO MAPA PARA REMOVER O PLUGIN
		if (it->first->getName() == namePlugin) {
			pluginsListeners.erase(it->first);
			break;
		}
	}
}

void XMPPNegotiation::notifyAdaptation(std::string paramName, std::map<
		std::string, std::string>& params) {

}

const char* XMPPNegotiation::getName() const {

}

std::string XMPPNegotiation::retrievePluginInformation(std::string info,
		std::string subInfo) throw (OperationNotSupportedException) {

}

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

	mClient->registerTagHandler(this, MessageConstants::TAG_HAS_SUPPORT,
			MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	mClient->registerTagHandler(this, MessageConstants::TAG_IQ,
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

void SimpleClient::handleTag(Tag *tag) {
	std::string nameTag = tag->name();
	if (nameTag == MessageConstants::TAG_HAS_SUPPORT)
		newHasSupportEvent(tag);
	else
		newIqEvent(tag);
}

void SimpleClient::newHasSupportEvent(Tag* tag) {
	list<Tag::Attribute*> listAttr = tag->attributes();
	map<std::string, std::string> mapAttr;
	for(list<Tag::Attribute*>::iterator it = listAttr.begin(); it != listAttr.end(); it++){
		//mapAttr[*it->name()] = *it->value();
		*it->name();
	}

	xmppNegotiation->updateAttrHasSuport(mapAttr);
}

void SimpleClient::newIqEvent(Tag* tag) {
	std::string typeIq = tag->findAttribute(MessageConstants::IQ_ID_TYPE);
	if (atoi(typeIq.c_str()) == MessageConstants::RESULT)
		printf("asd");
	//else if (atoi(typeIq.c_str()) == MessageConstants::RETRIVE)
	//xmppNegotiation->retrievePluginInformation("info", "subinfo");
	//else
	//xmppNegotiation->notifyAdaptation("paramName", map<std::string,
	//		std::string> params);

}
