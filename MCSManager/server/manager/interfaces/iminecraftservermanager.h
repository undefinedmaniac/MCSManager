#ifndef IMINECRAFTSERVERMANAGER_H
#define IMINECRAFTSERVERMANAGER_H

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
    virtual void stopServer() = 0;
};

#endif // IMINECRAFTSERVERMANAGER_H
