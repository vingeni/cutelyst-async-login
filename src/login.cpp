#include "login.h"
#include "authstoreasql.h"

#include <QDebug>
#include <Cutelyst/Plugins/Authentication/authentication.h>
#include <Cutelyst/async.h>
#include <adatabase.h>
#include <aresult.h>
#include <apool.h>

using namespace Cutelyst;
using namespace ASql;

Login::Login(AuthStoreASql* store, QObject *parent) : Controller(parent)
{
    m_store = store;
}

Login::~Login()
{
}

void Login::index(Context *c)
{
    // get parameters
    const ParamsMultiMap params = c->request()->bodyParams();
    const QString username = params.value(QStringLiteral("username"));
    const QString password = params.value(QStringLiteral("password"));

    qWarning() << "checking params";
    
    // If the username and password values were found in form
    if (username.isNull() || password.isNull()) {
        c->response()->body() = "User or password empty";
        c->response()->setStatus(Response::NotFound);
        return;
    }

    qWarning() << "starting async request";
    
    //ASql async search
    auto db = APool::database();
    ASync a(c);

    db.exec("select * from users where username=$1",
            { username },
            [a, c, this, params, username, password](AResult result) {

                if (result.error()) {
                    qWarning() << "SQL Request failed: " << result.errorString();
                    c->response()->setStatus(Response::InternalServerError);
                    return;
                }

                if (result.size() == 0) {
                    qWarning() << "User not found (" << username << ')';
                    c->response()->body() = "User not found";
                    c->response()->setStatus(Response::NotFound);
                    return;
                }

                qWarning() << "User found in SQL";
                AuthenticationUser u(username);
                for (int i = 0; i < result.fields(); ++i) {
                    u.insert(result.fieldName(i), result[0].value(i));
                }
                m_store->setUser(u);

                // Authenticate
                qDebug() << "Authenticating process for" << username;
                if (!Authentication::authenticate(c, params)) {
                    c->response()->body() = "Not authenticated";
                    c->response()->setStatus(Response::Unauthorized);
                    return;
                }

                c->response()->body() = "Authentication complete";
                c->response()->setStatus(Response::OK);
            });
}

