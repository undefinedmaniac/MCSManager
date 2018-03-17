#ifndef IMINECRAFTSERVERMANAGER_H
#define IMINECRAFTSERVERMANAGER_H

#include "core/mcsmanagercorebase.h"

#include "config/interfaces/iservermanagerconfig.h"

class IMinecraftServer;
class IServerManagerConfig;

class IMinecraftServerManager : public McsManagerCoreBase
{
public:
    virtual ~IMinecraftServerManager() {}

    virtual const IServerManagerConfig *config() const = 0;

    virtual void setServer(IMinecraftServer *server) = 0;
    virtual IMinecraftServer *server() = 0;

    virtual void startServer() = 0;
    virtual void stopServer(IServerManagerConfig::ShutdownBehavior behavior =
            IServerManagerConfig::DoNothing, const QString &altServer = "") = 0;
};

#endif // IMINECRAFTSERVERMANAGER_H
