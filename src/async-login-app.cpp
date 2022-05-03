#include "async-login-app.h"
#include "authstoreasql.h"
#include "root.h"
#include "login.h"

#include <QDebug>
#include <Cutelyst/Plugins/Session/Session>
#include <Cutelyst/Plugins/Authentication/authentication.h>
#include <Cutelyst/Plugins/Authentication/credentialpassword.h>
#include <Cutelyst/Plugins/Authentication/authenticationrealm.h>
#include <apool.h>
#include <apg.h>

using namespace Cutelyst;
using namespace ASql;

async_login::async_login(QObject *parent) : Application(parent)
{
    m_store = new AuthStoreASql;
}

async_login::~async_login()
{
}

bool async_login::init()
{
    // create the db pool
    APool::create(APg::factory("postgres:///"));

    // authentication settings
    auto auth = new Authentication(this);
    
    auto credential = new CredentialPassword;
    credential->setPasswordField(QStringLiteral("password"));
    credential->setPasswordType(CredentialPassword::Clear);
    
    auto realm = new AuthenticationRealm(m_store, credential);
        
    auth->addRealm(realm);

    new Session(this);
    new Root(this);
    new Login(m_store, this);

    return true;
}

