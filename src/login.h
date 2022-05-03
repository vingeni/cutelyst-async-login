#ifndef LOGIN_H
#define LOGIN_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class AuthStoreASql;

class Login : public Controller
{
    Q_OBJECT
public:
    explicit Login(AuthStoreASql* store, QObject *parent = nullptr);
    ~Login();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

private:
  AuthStoreASql* m_store;
};

#endif //LOGIN_H

