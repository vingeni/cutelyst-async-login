#include "authstoreasql.h"


using namespace Cutelyst;



AuthStoreASql::AuthStoreASql(QObject *parent) : AuthenticationStore(parent)
{
}


AuthenticationUser AuthStoreASql::findUser(Context *c, const ParamsMultiMap &userinfo)
{
    AuthenticationUser res(m_authuser);

    m_authuser = AuthenticationUser();
    
    return res;
}


void AuthStoreASql::setUser(const AuthenticationUser& u)
{
    m_authuser = u;
}
