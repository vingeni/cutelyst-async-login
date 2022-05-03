#include "root.h"

#include <Cutelyst/Plugins/Authentication/authentication.h>
#include <Cutelyst/async.h>
#include <adatabase.h>
#include <aresult.h>
#include <apool.h>

using namespace Cutelyst;
using namespace ASql;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    if (!Authentication::userExists(c)) {
        c->response()->body() = "User not authenticated";
        c->response()->setStatus(Response::Unauthorized);
    } else {
        c->response()->body() = "User authenticated";
    }
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

