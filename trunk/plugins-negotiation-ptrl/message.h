#ifndef MESSAGE_H
#define MESSAGE_H

#include <gloox/message.h>
#include <gloox/gloox.h>
#include <gloox/messagehandler.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace gloox;

class MessageConstants
{
public:

	static const std::string TAG_HAS_SUPPORT;
	static const std::string TAG_IQ;

	static const std::string IQ_ID_TYPE;
	static const std::string TAG_NAMESPACE_NEGOTIATION_PLUGIN;
	static const std::string FROM;
	static const std::string TO;

	enum IqType {
			RESULT,
			RETRIVE,
			NOTIFY,
			NONE
	};

};

class MessageCreator
{

private:
	static MessageCreator* instance;
	MessageCreator();
	Tag* newSimpleTag(const std::string& to, const std::string& from, MessageConstants::IqType = MessageConstants::NONE);
	Tag* addAttributesInNewTag(std::map<std::string, std::string> attributes);

public:
	static MessageCreator* getInstance();
	Tag* newHasSuport(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes);
	Tag* newIqResult(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes);
	Tag* newIqRetrive(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes);
	Tag* newIqNotify(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes);
};

#endif // MESSAGE_H
