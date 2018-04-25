#ifndef IMCSERVERBUILDER_H
#define IMCSERVERBUILDER_H

#include "mcsmanager/config/configglobal.h"

class IMcServer;
class IServerConfig;
class QString;

class IMcServerBuilder
{
public:
    virtual ~IMcServerBuilder() {}

    virtual IMcServer *getMcServer(IServerConfig *serverConfig) = 0;
    virtual void deleteMcServer(IMcServer *server) = 0;

    virtual ConfigGlobal::DefaultList getAddonDefaults() const = 0;
};

#endif // IMCSERVERBUILDER_H
