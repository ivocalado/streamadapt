#ifndef SIMPLESERVER_H__
#define SIMPLESERVER_H__

#include <glooxd/authenticationhandler.h>
#include <glooxd/c2s.h>
#include <glooxd/certificateprovider.h>
#include <glooxd/rosterprovider.h>

#include <gloox/loghandler.h>
#include <gloox/jid.h>
#include <gloox/logsink.h>

#include <string>

#include <cc++/thread.h>

#ifdef	CCXX_NAMESPACES
using namespace std;
using namespace ost;
#endif

class GLOOXD_API SimpleServer : gloox::LogHandler, glooxd::AuthenticationHandler, glooxd::RosterProvider,
glooxd::CertificateProvider, public Thread
{
public:
	/**
	 * Constructor.
	 */
	SimpleServer();

	/**
	 * Destructor.
	 */
	~SimpleServer();

	void run();

	// reimplemented from AuthenticationHandler
	virtual bool handleUserRequest( const gloox::JID& bare );

	// reimplemented from AuthenticationHandler
	virtual bool handleSASLPlain( const std::string& authzid,
			const std::string& authcid,
			const std::string& password );

	// reimplemented from gloox::LogHandler
	virtual void handleLog( gloox::LogLevel level, gloox::LogArea area, const std::string& message );

	// reimplemented from RosterProvider
	virtual const glooxd::Roster getRoster( const gloox::JID& jid );

	// reimplemented from CertificateProvider
	virtual const std::string handleCertificateRequest( const std::string& domain );

	virtual const std::string handleKeyRequest( const std::string& domain );

private:
	gloox::LogSink m_log;

};

#endif // SIMPLESERVER_H__
