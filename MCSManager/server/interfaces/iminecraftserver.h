#ifndef IMINECRAFTSERVER_H
#define IMINECRAFTSERVER_H

#include "server/interfaces/iminecraftserverio.h"
#include "server/interfaces/iminecraftserverprocess.h"
#include "server/interfaces/iminecraftserveraddonmanager.h"

class IMinecraftServerManager;

class IMinecraftServer : public IMinecraftServerProcess, public IMinecraftServerIo,
        public IMinecraftServerAddonManager
{
public:
    virtual ~IMinecraftServer() {}

    virtual void setServerManager(IMinecraftServerManager *serverManager) = 0;
    virtual IMinecraftServerManager *serverManager() = 0;
};

Q_DECLARE_INTERFACE(IMinecraftServer, "IMinecraftServer")

#endif // IMINECRAFTSERVER_H
