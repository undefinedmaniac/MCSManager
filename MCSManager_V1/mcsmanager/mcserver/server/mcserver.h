#ifndef MCSERVER_H
#define MCSERVER_H

#include "interfaces/imcserver.h"
#include "serverconfigreader.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"

#include <QObject>
#include <QProcess>
#include <QString>
#include <QHash>
#include <QDebug>

namespace Server { class McServer; }

class Server::McServer : public Server::IMcServer, public Core::McsManagerCoreChild
{
    Q_OBJECT
public:
    McServer(Config::IServerConfig *config, Core::IMcsManagerCore *core = nullptr,
             QObject *parent = nullptr);
    ~McServer();

    // IMcServer interface
    QString getName() const;
    Config::IServerConfig *getConfig() override;

    void addAddon(Addon::IMcServerAddon *addon) override;
    void removeAddon(const QString &addonName) override;
    Addon::IMcServerAddon *getAddon(const QString &addonName) override;
    QStringList getAddonList() const override;

    void start() override;
    void restart() override;
    void stop() override;
    bool isRunning() const override;

protected:
    Core::IMcsManagerCore *getCore() override;
    Config::IConfigManager *getConfigManager()  override;
    Backup::IBackupManager *getBackupManager()  override;
    Server::IMcServerBuilder *getServerBuilder()  override;

private slots:
    void serverStarted();
    void serverStopped(int exitCode, QProcess::ExitStatus exitStatus);
    void serverErrorOccurred(QProcess::ProcessError errorType);

private:
    enum ServerState {
        Started, Starting, Stopped, Stopping, Restarting
    };

    bool mFirstStart = true;

    Config::IServerConfig *mConfig;
    bool mIsRealServer;
    Config::ShutdownBehavior mShutdownBehavior;
    QString mAltServer;

    QProcess mProcess;
    ServerState mState = Stopped;

    QHash<QString, Addon::IMcServerAddon*> mAddons;

    void stopServer();

    void initAddons();
    void startAddons();
    void stopAddons();
    void deleteAddon(Addon::IMcServerAddon *addon);
};

#endif // MCSERVER_H
