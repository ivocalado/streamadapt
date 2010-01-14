/*
 * streamsession.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef STREAMSESSION_H_
#define STREAMSESSION_H_

#include "session.h"
#include "trpsession.h"

namespace infrastream {

class StreamSession: public infrastream::Session {
	TransportSession* trpSession;
public:
	StreamSession(TransportSession* transportSession,
			PluginNegotiationPtrlIF* negotiation)
			throw(CannotCreateSessionException);
	virtual ~StreamSession();
};

}

#endif /* STREAMSESSION_H_ */
