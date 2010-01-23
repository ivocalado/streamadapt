#include "message.h"
#include <stdlib.h>

const std::string MessageConstants::IQ_NOTIFY = "iq-notify";
const std::string MessageConstants::IQ_NOTIFY_RESPONSE = "iq-notify-response";

const std::string MessageConstants::IQ_RETRIEVE = "iq-retrieve";
const std::string MessageConstants::IQ_RETRIEVE_RESPONSE =
		"iq-retrieve-response";

const std::string MessageConstants::ATTIBUTE_REQUIRED = "attribute-required";
const std::string MessageConstants::ATTIBUTE_VALUE = "attribute-value";

const std::string MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN =
		"http://embedded.ufcg.edu.br";
const std::string MessageConstants::FROM = "from";
const std::string MessageConstants::TO = "to";

const std::string MessageConstants::MESSAGE_TYPE;
const std::string MessageConstants::STREAM;
const std::string MessageConstants::TRANSPORT;
const std::string MessageConstants::EMPTY_STRING;

/*
 MessageCreator* MessageCreator::instance = 0;

 MessageCreator::MessageCreator() {
 }

 MessageCreator* MessageCreator::getInstance() {
 if (instance == 0)
 instance = new MessageCreator();
 return instance;
 }
 */
MessageCreator::MessageCreator(std::string to, std::string from) {
	this->to = to;
	this->from = from;
}

Tag* MessageCreator::newSimpleTag(std::string iqType, std::string messageType) {

	Tag* m = new Tag(iqType);
	if (messageType != MessageConstants::EMPTY_STRING)
		m->addAttribute(MessageConstants::MESSAGE_TYPE, messageType);
	m->addAttribute(MessageConstants::TO, to);
	m->addAttribute(MessageConstants::FROM, from);
	m->setXmlns(MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	return m;
}

Tag* MessageCreator::addAttributesInNewTag(
		std::map<std::string, std::string> attributes) {
	Tag* tag = new Tag("Attributes");
	for (std::map<std::string, std::string>::const_iterator it =
			attributes.begin(); it != attributes.end(); it++) {
		tag->addAttribute(it->first, it->second);
	}
	return tag;
}

Tag* MessageCreator::newIqNotify(std::map<std::string, std::string> attributes,
		std::string messageType) {
	Tag* tag = newSimpleTag(MessageConstants::IQ_NOTIFY, messageType);
	tag->addChild(addAttributesInNewTag(attributes));
	return tag;
}

Tag* MessageCreator::newIqNotifyResponse(std::string messageType) {
	Tag* tag = newSimpleTag(MessageConstants::IQ_NOTIFY_RESPONSE,
			messageType);
	return tag;
}

Tag* MessageCreator::newIqRetrieve(std::string attribute) {
	Tag* tag = newSimpleTag(MessageConstants::IQ_RETRIEVE);
	tag->addAttribute(MessageConstants::ATTIBUTE_REQUIRED, attribute);
	return tag;
}

Tag* MessageCreator::newIqRetrieveResponse(std::string attribute,
		std::string value) {
	Tag* tag = newSimpleTag(MessageConstants::IQ_RETRIEVE_RESPONSE);
	tag->addAttribute(MessageConstants::ATTIBUTE_REQUIRED, attribute);
	tag->addAttribute(MessageConstants::ATTIBUTE_VALUE, value);
	return tag;
}
