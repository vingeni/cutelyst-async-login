#include "authstoreasql.h"


using namespace Cutelyst;



AuthStoreASql::AuthStoreASql(QObject *parent) : AuthenticationStore(parent)
{
    m_idField = "username";
}


AuthenticationUser AuthStoreASql::findUser(Context *c, const ParamsMultiMap &userinfo)
{
    if (m_authuser.id() == userinfo.value("m_idField"))
        return m_authuser;

    return AuthenticationUser();
}


void AuthStoreASql::setUser(const AuthenticationUser& u)
{
    m_authuser = u;
}
