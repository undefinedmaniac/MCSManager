#ifndef MINECRAFTSERVERMANAGER_H
#define MINECRAFTSERVERMANAGER_H

#include <QObject>

#include "core/mcsmanagercorebase.h"

#include "config/interfaces/iservermanagerconfig.h"

#include "server/interfaces/iminecraftserver.h"
#include "server/manager/interfaces/iminecraftservermanager.h"

class MinecraftServerManager : public QObject, public McsManagerCoreBase,
        public IMinecraftServerManager
{
    Q_OBJECT
public:
    MinecraftServerManager();

    void setConfig(const IServerManagerConfig *config) override;
    const IServerManagerConfig *config() const override;
    void setServer(IMinecraftServer *server) override;
    IMinecraftServer *server() override;
    void startServer() override;
    void stopServer(IServerManagerConfig::ShutdownBehavior behavior =
            IServerManagerConfig::DoNothing) override;

private slots:
    void serverStoped();

private:
    const IServerManagerConfig *mConfig = nullptr;
    IMinecraftServer *mServer;
};

#endif // MINECRAFTSERVERMANAGER_H
