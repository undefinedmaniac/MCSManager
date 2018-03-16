#ifndef IMINECRAFTSERVERMANAGER_H
#define IMINECRAFTSERVERMANAGER_H

#include "config/interfaces/iservermanagerconfig.h"

class IMinecraftServer;
class IServerManagerConfig;

class IMinecraftServerManager
{
public:
    virtual ~IMinecraftServerManager() {}

    virtual void setConfig(const IServerManagerConfig *config) = 0;
    virtual const IServerManagerConfig *config() const = 0;

    virtual void setServer(IMinecraftServer *server) = 0;
    virtual IMinecraftServer *server() = 0;

    virtual void startServer() = 0;
    virtual void stopServer(IServerManagerConfig::ShutdownBehavior behavior, const QString &altServer) = 0;
};

#endif // IMINECRAFTSERVERMANAGER_H
