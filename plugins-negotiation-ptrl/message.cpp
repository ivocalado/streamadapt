#include "message.h"
#include <stdlib.h>

const std::string MessageConstants::TAG_IQ = "iq";
const std::string MessageConstants::TAG_HAS_SUPPORT = "has_suport";
const std::string MessageConstants::IQ_ID_TYPE = "iq_type";
const std::string MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN =
		"http://embedded.ufcg.edu.br";

const std::string MessageConstants::FROM = "from";
const std::string MessageConstants::TO = "to";

MessageCreator* MessageCreator::instance = 0;

MessageCreator::MessageCreator() {
	srand((unsigned) time(0));
}

MessageCreator* MessageCreator::getInstance() {
	if (instance == 0)
		instance = new MessageCreator();
	return instance;
}

Tag* MessageCreator::newSimpleTag(const std::string& to,
		const std::string& from, MessageConstants::IqType type) {
	Tag* m;
	switch(type) {
	case MessageConstants::RESULT :
		m = new Tag(MessageConstants::TAG_IQ);
		m->addAttribute(MessageConstants::IQ_ID_TYPE, type);
		break;
	case MessageConstants::RETRIVE :
		m = new Tag(MessageConstants::TAG_IQ);
		m->addAttribute(MessageConstants::IQ_ID_TYPE, type);
		break;
	case MessageConstants::NOTIFY :
		m = new Tag(MessageConstants::TAG_IQ);
		m->addAttribute(MessageConstants::IQ_ID_TYPE, type);
		break;
	case MessageConstants::NONE :
		m = new Tag(MessageConstants::TAG_HAS_SUPPORT);
		break;
	};
	m->addAttribute(MessageConstants::TO, to);
	m->addAttribute(MessageConstants::FROM, from);
	m->setXmlns(MessageConstants::TAG_NAMESPACE_NEGOTIATION_PLUGIN);
	return m;
}

Tag* MessageCreator::addAttributesInNewTag(std::map<std::string, std::string> attributes){
	Tag* tag = new Tag("Attributes");
	for (std::map<std::string, std::string>::const_iterator it = attributes.begin(); it != attributes.end(); it++) {
		tag->addAttribute(it->first, it->second);
	}
	return tag;
}

Tag* MessageCreator::newHasSuport(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes){
	Tag* tag = newSimpleTag(to, from);
	tag->addChild(addAttributesInNewTag(attributes));
	return tag;
}

Tag* MessageCreator::newIqResult(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes){
	Tag* tag = newSimpleTag(to, from, MessageConstants::RESULT);
	tag->addChild(addAttributesInNewTag(attributes));
	return tag;
}

Tag* MessageCreator::newIqRetrive(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes){
	Tag* tag = newSimpleTag(to, from, MessageConstants::RETRIVE);
	tag->addChild(addAttributesInNewTag(attributes));
	return tag;
}

Tag* MessageCreator::newIqNotify(const std::string& to, const std::string& from, std::map<std::string, std::string> attributes){
	Tag* tag = newSimpleTag(to, from, MessageConstants::NOTIFY);
	tag->addChild(addAttributesInNewTag(attributes));
	return tag;
}
