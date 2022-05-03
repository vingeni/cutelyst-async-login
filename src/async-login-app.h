#ifndef ASYNC_LOGIN_H
#define ASYNC_LOGIN_H

#include <Cutelyst/Application>

using namespace Cutelyst;

class AuthStoreASql;


class async_login : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "async_login")
public:
    Q_INVOKABLE explicit async_login(QObject *parent = nullptr);
    ~async_login();

    bool init();

 private:
    AuthStoreASql* m_store;
};

#endif //ASYNC_LOGIN_H

