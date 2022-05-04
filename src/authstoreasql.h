#ifndef AUTHSTORESQL_H
#define AUTHSTORESQL_H

#include <Cutelyst/Plugins/Authentication/authenticationstore.h>

using namespace Cutelyst;

class AuthStoreASql : public AuthenticationStore
{
public:
    explicit AuthStoreASql(QObject *parent = 0);

    virtual AuthenticationUser findUser(Context *c, const ParamsMultiMap &userinfo) override;

    void setUser(const AuthenticationUser& u);
    
private:
    QString m_idField;
    AuthenticationUser m_authuser;
};

#endif // AUTHSTORESQL_H
