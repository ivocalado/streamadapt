#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/taghandler.h>
#include <gloox/iqhandler.h>
#include <gloox/tag.h>
#include <stdio.h>
#include <iostream>
#include "message.h"
#include <cc++/thread.h>

using namespace gloox;
using namespace std;
using namespace ost;

class XMPPNegotiation;

/**
 * Classe que implementa um cliente XMPP que se conecta a um servido XMPP, este cliente se
 * conecta, envia e recebe menssagens XMPP atraves de TAGS
 */
class SimpleClient: public Thread, public TagHandler {

private:
	XMPPNegotiation* xmppNegotiation; /*Objeto que eh responsavel pelas acoes do recebimento das mensagens do cliente XMPP*/

public:
	/**
	 * Metodo construtor da classe SimpleClient
	 * @param username nome do cliente XMPP cadastrado no servidor
	 * @param password senha do cliente XMPP
	 * @param plugin referencia ao objeto do tipo XMPPNegotiation
	 * @param host endereco IP do servidor XMPP
	 * @param port Porta do servidor XMPP
	 */
	SimpleClient(std::string username, std::string password,
			XMPPNegotiation* plugin, std::string host = "localhost", int port =
					5222);

	/**
	 * Metodo destrutor
	 */
	virtual ~SimpleClient();

	/**
	 * Metodo que conecta o cliente ao servidor XMPP.
	 */
	void login();

	/**
	 * Metodo que desconecta o cliente do servidor XMPP.
	 */
	void logout();

	/**
	 * Metodo que envia mensagens XMPP enderecadas a um outro cliente XMPP.
	 * @param mss menssagem a ser enviada
	 */
	void sendMessage(Tag* mss);

	/**
	 * Metodo responsavel pelo recebimento das mensagens XMPP.
	 * @param tag estrutura Gloox que contem as menssagens recebidas pelo cliente XMPP
	 */
	virtual void handleTag(Tag *tag);

	/**
	 * Metodo responsavel pela acao de recebimento da mensagem de HasSuport do cliente XMPP.
	 * @param tag estrutura Gloox que contem as menssagens recebidas pelo cliente XMPP
	 */
	void newHasSupportEvent(Tag* tag);

	/**
	 * Metodo que faz o tratamento da mensagem XMPP recebida.
	 * @param estrutura Gloox que contem as menssagens recebidas pelo cliente XMPP
	 */
	void newIqEvent(Tag* tag);

	/**
	 * Metodo que executa a acao de start da implementacao de thread.
	 */
	void run(void);

private:

	/* Cliente XMPP interno*/
	Client* mClient;
};

#ifndef XMPPNEGOTIATION_H_
#define XMPPNEGOTIATION_H_

#include "../streamadapt/inc/plugins/pluginnegotiation.h"
#include "../streamadapt/inc/infraexceptions.h"
//#include "simpleserver.h"

#include <string>
#include <map>
#include <list>

/**
 * Classe responsavel pelo gerenciamento da negociacao entre cliente-servidor XMPP.
 * Possui um cliente e um servidor XMMP que são gerenciados para o tratamento de envio/recebimento
 * de menssagens XMPP.
 */
class XMPPNegotiation: public PluginNegotiationPtrlIF {

private:

	bool isServer; /* Identificador responsavel por determinar se o objeto possui um servidor integrado */
	SimpleClient* client; /* Objeto responsavel pelas acoes de envio e recebimento de menssagens XMPP */
	const char* name; /* Nome do plugin */
	//SimpleServer* server; /* Objeto responsavel pelo gerenciamento dos clientes XMPP */
	map<std::string, list<PluginBase*> > pluginsListeners; /* Mapa que contem os plugins interessados em atributos */
	map<std::string, std::string> attHasSuport; /* Mapa que contem os atributos suportados pelo cliente remoto */

	/**
	 * Funcao que verifica se um plugin jah esta adicionado a uma lista.
	 */
	bool containsInList(list<PluginBase*> list, PluginBase* plugin);

public:

	/**
	 * Metodo construtor da classe XMPPNegotiation
	 */
	XMPPNegotiation();

	/**
	 * Metodo destrutor
	 */
	virtual ~XMPPNegotiation();

	/**
	 * Metodo que inicia a negociacao entre as entidades cliente/servidor XMPP.
	 * @param localIP Endereco IP local.
	 * @param localPort Porta local.
	 * @param remoteIp Endereco IP do servidor remoto XMPP.
	 * @param remotePort Porta do servidor remoto XMPP.
	 * @param params Parametros de configuracao.
	 */
	virtual void initNegotiation(std::string localIp, int localPort,
			std::string remoteIp, int remotePort, std::map<std::string,
					std::string>* params = 0)
			throw (OperationNotPerfomedException);

	/**
	 * Metodo que cadastram plugins interessador a uma lista de atributos.
	 * @param plugin Objeto do tipo plugin
	 * @param attributes Lista de atributos de interesse do plugin
	 */
	void addPluginListener(PluginBase* plugin, list<std::string> attributes);

	/**
	 * Metodo que remove um plugin jah cadastrado
	 * @param namePlugin nome do plugin a ser retirado
	 */
	void removePluginListener(PluginBase* plugin);

	/**
	 * Metodo que encerra a negociacao entre cliente/servidor XMPP.
	 */
	virtual void shutdownNegotiation();

	/**
	 * Metodo que atualiza o mapa que possui os atributos e valores suportados pela entidade remota.
	 * @param attr atributos que irao atualizar o mapa interno.
	 */
	void updateAttrHasSuport(map<std::string, std::string> attr);

	/**
	 * Metodo que informa o mapa de atributos e valores suportados pela entidade remota.
	 */
	map<std::string, std::string> getAttrHasSuport();

	void assignResponsibleMessageToPlugin(map<std::string, std::string> param);

	/**
	 * Metodo que realiza a acao de recebimento de modificaco de adaptacao.
	 */
	virtual void notifyAdaptation(std::string paramName, std::map<std::string,
			std::string>& params);

	/**
	 * Metodo que retorna o nome do plugin
	 */
	virtual const char* getName() const;

	/**
	 *
	 */
	virtual std::string retrievePluginInformation(std::string info,
			std::string subInfo = "") throw (OperationNotSupportedException);

};
#endif /* XMPPNEGOTIATION_H_ */
