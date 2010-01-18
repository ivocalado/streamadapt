#include "simpleserver.h"

#include <glooxd/c2s.h>
#include <glooxd/certificategenerator.h>
#include <glooxd/discomanager.h>
#include <glooxd/configmanager.h>
#include <glooxd/featurestarttls.h>
#include <glooxd/featuresasl.h>
#include <glooxd/featurecompression.h>
#include <glooxd/featureresourcebind.h>
#include <glooxd/featuresession.h>
#include <glooxd/messagemanager.h>
#include <glooxd/presencemanager.h>
#include <glooxd/rostermanager.h>
#include <glooxd/router.h>
#include <glooxd/sm.h>
#include <glooxd/vcardmanager.h>

#include <gloox/gloox.h>

#include <cstdio>

using namespace glooxd;

SimpleServer::SimpleServer() {}

SimpleServer::~SimpleServer() {}

void SimpleServer::run()
{
	m_log.registerLogHandler( gloox::LogLevelDebug,
			gloox::LogAreaAll
			| static_cast<gloox::LogArea>( LogAreaC2S )
			| static_cast<gloox::LogArea>( LogAreaClient )
			| static_cast<gloox::LogArea>( LogAreaSM )
			| static_cast<gloox::LogArea>( LogAreaDM )
			| static_cast<gloox::LogArea>( LogAreaRouter ),
			this );

	ConfigManager cm( m_log );

	Router r( cm, m_log );

	SM sm( r, cm, m_log, this );
	sm.addPlugin( new RosterManager( sm, r, this ) );
	sm.addPlugin( new PresenceManager( sm, r, this ) );
	sm.addPlugin( new MessageManager( sm, r, this ) );
	sm.addPlugin( new VCardManager( sm, r ) );
	sm.addPlugin( new DiscoManager( sm, r ) );

	C2S c2s( r, cm, m_log, sm );
	c2s.registerStreamFeature( new FeatureSASL( this ) );
	c2s.registerStreamFeature( new FeatureCompression() );
	c2s.registerStreamFeature( new FeatureResourceBind( sm ) );
	c2s.registerStreamFeature( new FeatureSession() );

	cm.addC2SInterface();
	cm.bindDomain( "boom", gloox::EmptyString, 5222 );

	while( true )
	{
		r.run();
		sm.run();
		c2s.run();
	}
}

bool SimpleServer::handleUserRequest( const gloox::JID& bare )
{
	printf( "user account checked: %s\n", bare.full().c_str() );
	return true;
}

bool SimpleServer::handleSASLPlain( const std::string& authzid,
		const std::string& authcid,
		const std::string& password )
{
	printf( "SASL PLAIN requested:\n    authzid: %s,\n    authcid: %s,\n    password: %s\n", authzid.c_str(), authcid.c_str(), password.c_str() );
	return true;
}

const Roster SimpleServer::getRoster( const gloox::JID& /*jid*/ )
{
	glooxd::Roster rm;
	rm.insert( std::make_pair( "client_local@boom", gloox::S10nBoth ) );
	rm.insert( std::make_pair( "client_remote@boom", gloox::S10nBoth ) );
	return rm;
}

const std::string SimpleServer::handleKeyRequest( const std::string& domain )
{
	printf( "private key requested for %s\n", domain.c_str() );
	return "/tmp/server.key";
}

const std::string SimpleServer::handleCertificateRequest( const std::string& domain )
{
	printf( "cert requested for %s\n", domain.c_str() );

	const std::string cert = "/tmp/" + domain + ".crt";
	if( !util::generateCertificate( domain, "/tmp/server.key",
			cert, 1024, 365, 1 ) )
	{
		printf( "generating cert for %s failed\n", domain.c_str() );
		return gloox::EmptyString;
	}

	return cert;
}

void SimpleServer::handleLog( gloox::LogLevel level, gloox::LogArea area, const std::string& message )
{
	printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}
