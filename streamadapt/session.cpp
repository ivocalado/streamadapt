/*
 * session.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include "inc/session.h"

namespace infrastream {

Session::Session(PluginNegotiationPtrlIF* negotiation)
		throw(CannotCreateSessionException) {
	if (negotiation)
		this->negotiation = negotiation;
	else {
		log_error("Error on create session. A valid negotiation session is required");
		throw CannotCreateSessionException("A negotiation object is required!");
	}
}

Session::~Session() {
	// TODO Auto-generated destructor stub
}

PluginNegotiationPtrlIF* Session::getNegotiation() const{
	return negotiation;
}

}
