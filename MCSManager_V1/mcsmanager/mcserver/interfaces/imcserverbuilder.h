#ifndef IMCSERVERBUILDER_H
#define IMCSERVERBUILDER_H

#include "mcsmanager/config/configglobal.h"

class QString;

namespace Config { class IServerConfig; }

namespace Server
{
    class IMcServer;
    class IMcServerBuilder;
}

class Server::IMcServerBuilder
{
public:
    virtual ~IMcServerBuilder() {}

    virtual Server::IMcServer *getMcServer(Config::IServerConfig *serverConfig) = 0;
    virtual void deleteMcServer(Server::IMcServer *server) = 0;
};

#endif // IMCSERVERBUILDER_H
