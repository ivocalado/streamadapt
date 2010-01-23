#ifndef MESSAGE_H
#define MESSAGE_H

#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/messagehandler.h>
#include <stdio.h>
#include <cstdlib>
#include <map>

using namespace gloox;

class MessageConstants {
public:

	/*
	 <iq>
	 <attribute-required>RTT</attribute-required>
	 </iq>

	 <iq-response>
	 <attribute-required>RTT</attribute-required>
	 <attribute-value>2.46/attribute-value>
	 <iq-response>
	 */
	/*
	 <notify>
	 <transport>
	 <param1>value1</param1>
	 <param2>value2</param>
	 </transport>
	 </notify>
	 */
	static const std::string IQ_NOTIFY;
	static const std::string IQ_NOTIFY_RESPONSE;

	static const std::string IQ_RETRIEVE;
	static const std::string IQ_RETRIEVE_RESPONSE;

	static const std::string ATTIBUTE_REQUIRED;
	static const std::string ATTIBUTE_VALUE;

	static const std::string TAG_NAMESPACE_NEGOTIATION_PLUGIN;
	static const std::string FROM;
	static const std::string TO;

	static const std::string MESSAGE_TYPE;
	static const std::string STREAM;
	static const std::string TRANSPORT;
	static const std::string EMPTY_STRING;

};

class MessageCreator {

private:
	//static MessageCreator* instance;
	//MessageCreator();

	std::string to;
	std::string from;

	Tag* newSimpleTag(std::string iqType, std::string messageType = MessageConstants::EMPTY_STRING);
	Tag* addAttributesInNewTag(std::map<std::string, std::string> attributes);

public:
	//static MessageCreator* getInstance(std::string);
	MessageCreator(std::string to, std::string from);

	Tag* newIqNotify(std::map<std::string, std::string> attributes,
			std::string messageType = MessageConstants::EMPTY_STRING);
	Tag* newIqNotifyResponse(std::string messageType =
			MessageConstants::EMPTY_STRING);
	Tag* newIqRetrieve(std::string attribute);
	Tag* newIqRetrieveResponse(std::string attribute, std::string value);
};

#endif // MESSAGE_H
