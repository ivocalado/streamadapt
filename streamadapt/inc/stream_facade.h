/*
 * stream_facade.h
 *
 *  Created on: 14/07/2009
 *      Author: ivocalado
 */

#ifndef STREAM_FACADE_H_
#define STREAM_FACADE_H_

#include "stream_sink.h"
#include "stream_src.h"
#include "address.h"
#include "stream_controller.h"
#include <map>
#include <string>
#include "core.h"
namespace core {

class StreamFacade {
	static StreamFacade* instance;
	StreamFacade();
	Core<> *core;

public:
	StreamFacade* getInstance();
	virtual ~StreamFacade();
	std::string /*stream id*/ createStream(Address/*stream address */, Address/*control address */,
			StreamSrc*, StreamSink*, std::string /*plugin.xml*/, StreamController*,
			std::map<std::string, std::string>* /*properties*/);
//	void createStream(ost::InetAddress&);
//	bool createChannel(ost::InetAddress&, )

};

};

#endif /* STREAM_FACADE_H_ */
