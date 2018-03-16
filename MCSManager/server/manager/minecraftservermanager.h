#ifndef MINECRAFTSERVERMANAGER_H
#define MINECRAFTSERVERMANAGER_H

#include <QObject>
#include <QDebug>

#include "core/mcsmanagercorebase.h"
#include "core/interfaces/imcsmanagercore.h"

#include "config/interfaces/iserverconfig.h"
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
            IServerManagerConfig::DoNothing, const QString &altServer = "") override;

private slots:
    void serverStarted();
    void serverStopped();

private:
    enum InternalState {
        Idle, StartingServer, ServerStarted,
        StoppingServer, ServerStopped
    };

    InternalState mState = Idle;
    const IServerManagerConfig *mConfig = nullptr;
    IMinecraftServer *mServer = nullptr;

    void shutdownAction(IServerManagerConfig::ShutdownBehavior behavior,
                        const QString &altServer = "");
};

#endif // MINECRAFTSERVERMANAGER_H
