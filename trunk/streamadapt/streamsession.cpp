/*
 * streamsession.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include <streamsession.h>
#include <logger/logger.h>

namespace infrastream {

StreamSession::StreamSession(TransportSession* transportSession,
		PluginNegotiationPtrlIF* negotiation)
		throw(CannotCreateSessionException) :
	Session(negotiation) {
	if (transportSession) {
		log_info("Creating stream session");
		trpSession = transportSession;
	} else {
		log_error("Error on create session. A transport session is required");
		throw CannotCreateSessionException("A negotiation object is required!");
	}
}

StreamSession::~StreamSession() {

}

}
