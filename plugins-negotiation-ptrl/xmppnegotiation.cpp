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
		xmppNegotiation->receivedIqNotifyRespose(messageType);
	else if (message == MessageConstants::IQ_RETRIEVE)
		xmppNegotiation->receivedIqRetrieve(tag->findAttribute(
				MessageConstants::ATTIBUTE_REQUIRED));
	else
		xmppNegotiation->receivedIqRetrieveResponse(tag->findAttribute(
				MessageConstants::ATTIBUTE_REQUIRED), tag->findAttribute(
				MessageConstants::ATTIBUTE_VALUE));
}

//Class XMPPNegotiation
XMPPNegotiation::XMPPNegotiation() {
}

XMPPNegotiation::~XMPPNegotiation() {
	delete client;
	delete server;
}

/**
 * Metodo que armazena os parametros de transmissao do lado remoto
 */
void XMPPNegotiation::remoteAdaptation(
		map<std::string, std::string> attributes, std::string messageType) {
	//doSomething
}

/**
 * Metodo que recebe uma notificacao de parametros de transmissao do lado remoto, se faz necessario mandar uma
 * menssagem de confirmacao de recebimento para o lado remoto
 */
void XMPPNegotiation::receivedIqNotify(
		map<std::string, std::string> attributes, std::string messageType) {
	//remoteAdaptation (resolvido)
	remoteAdaptation(attributes, messageType);
	if (isServer)
		client->sendMessage(messageCreator->newIqNotifyResponse(messageType));
	else
		client->sendMessage(messageCreator->newIqNotifyResponse(messageType));
}

/**
 * Metodo que recebe a confirmacao do lado remoto o recebimento da menssagem enviada de IQNotify
 */
void XMPPNegotiation::receivedIqNotifyRespose(std::string messageType) {
	//off
}

/**
 * Metodo que recebe a solicitacao do lado remoto do valor de um atributo, assim que recebida a menssagem
 * deve-se obter o valor do atributo e enviar para o lado remoto a resposta (valor do atributo)
 */
void XMPPNegotiation::receivedIqRetrieve(std::string attribute) {
	std::string value = retrieveLastLocalEvent(attribute);
	if (isServer)
		client->sendMessage(messageCreator->newIqRetrieveResponse(attribute,
				value));
	else
		client->sendMessage(messageCreator->newIqRetrieveResponse(attribute,
				value));
}

/**
 * Metodo que recebe a resposta da requisicao do valor do atributo do lado remoto
 * Esse metodo deve atualizar a tabela que contem os valores do atributo solicitado remotamente
 */
void XMPPNegotiation::receivedIqRetrieveResponse(std::string attribute,
		std::string value) {
	attRetrive[attribute] = value;
	//atualizar o mapa (Resolvido)
	//retirar o messageType (Resolvido)
}

void XMPPNegotiation::initNegotiation(std::string localIp, int localPort,
		std::string remoteIp, int remotePort,
		std::map<std::string, std::string>* params)
		throw (OperationNotPerfomedException) {
	if ((*params)["server"] == "yes") {
		isServer = true;
		server = new SimpleServer();
		client = new SimpleClient("client_local@boom", "", this);
		messageCreator = new MessageCreator("client_remote@boom",
				"client_local@boom");
	} else {
		client = new SimpleClient("client_remote@boom", "", this, remoteIp,
				remotePort);
		messageCreator = new MessageCreator("client_local@boom",
				"client_remote@boom");
	}

	if (isServer)
		server->start();
		client->start();
}

void XMPPNegotiation::shutdownNegotiation() {
	//server->stop();
	client->logout();
}

/**
 * Metodo que notifica ao lado remoto os novos parametros de transmissao de stream
 * Eh um iq, e o outro lado deve responder que recebeu a menssagem corretamente
 */
void XMPPNegotiation::notifyAdaptation(std::string paramName, std::map<
		std::string, std::string>& params) {
	client->sendMessage(messageCreator->newIqNotify(params, paramName));
	//mando iqnotify (Resolvido)
	//paramName (Resolvido)
}

const char* XMPPNegotiation::getName() const {
	return name;
}

/**
 * Metodo que consulta o valor de um atributo do lado remoto que se encontra em uma mapa
 * ele consulta o mapa e apos isso manda um iqRetrive para atualizar a tabela com um novo valor
 * para o atributo pesquisado
 */
std::string XMPPNegotiation::retrievePluginInformation(std::string info,
		std::string subInfo) throw (OperationNotSupportedException) {
	client->sendMessage(messageCreator->newIqRetrieve(info));
	return attRetrive[info];
	//retorno o valor do mapa e disparo o iq (resolvido)
}
