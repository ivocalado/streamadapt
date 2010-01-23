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
	static MessageCreator* instance;
	MessageCreator();
	Tag* newSimpleTag(const std::string& to, const std::string& from,
			std::string iqType, std::string messageType);
	Tag* addAttributesInNewTag(std::map<std::string, std::string> attributes);

public:
	static MessageCreator* getInstance();
	Tag* newIqNotify(const std::string& to, const std::string& from, std::map<
			std::string, std::string> attributes, std::string messageType =
			MessageConstants::EMPTY_STRING);
	Tag* newIqNotifyResponse(const std::string& to, const std::string& from,
			std::string messageType = MessageConstants::EMPTY_STRING);
	Tag* newIqRetrieve(const std::string& to, const std::string& from,
			std::string attribute, std::string messageType =
					MessageConstants::EMPTY_STRING);
	Tag* newIqRetrieveResponse(const std::string& to, const std::string& from,
			std::string attribute, std::string value, std::string messageType =
					MessageConstants::EMPTY_STRING);
};

#endif // MESSAGE_H
