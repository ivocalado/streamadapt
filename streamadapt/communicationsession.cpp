/*
 * session.cpp
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#include <communicationsession.h>

namespace infrastream {

CommunicationSession::CommunicationSession(string _pluginName, string _libName)
		throw(CannotCreateSessionException) :
	pluginName(_pluginName), libName(_libName) {
	/*if (negotiation)
	 this->negotiation = negotiation;
	 else {
	 log_error("Error on create session. A valid negotiation session is required");
	 throw CannotCreateSessionException("A negotiation object is required!");
	 }*/
}

CommunicationSession::~CommunicationSession() {
	// TODO Auto-generated destructor stub
}


string CommunicationSession::getPluginName() const {
	return pluginName;
}
string CommunicationSession::getLibName() const {
	return libName;
}

}
