#ifndef MCSERVER_H
#define MCSERVER_H

#include "interfaces/imcserver.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "serverconfigreader.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"

#include <QObject>
#include <QProcess>
#include <QString>
#include <QHash>
#include <QDebug>

class McServer : public IMcServer, public McsManagerCoreChild
{
    Q_OBJECT
public:
    McServer(IServerConfig *config, IMcsManagerCore *core = nullptr,
             QObject *parent = nullptr);
    ~McServer();

    // IMcServer interface
    QString getName() const;
    IServerConfig *getConfig() override;

    void addAddon(IMcServerAddon *addon) override;
    void removeAddon(const QString &addonName) override;
    IMcServerAddon *getAddon(const QString &addonName) override;
    QStringList getAddonList() const override;

    void start() override;
    void restart() override;
    void stop() override;
    bool isRunning() const override;

protected:
    IMcsManagerCore *getCore() override;
    IConfigManager *getConfigManager()  override;
    IBackupManager *getBackupManager()  override;
    IMcServerBuilder *getServerBuilder()  override;

signals:
    void started();
    void stopped(bool expected);
    void error(QString errorMessage);

private slots:
    void serverStarted();
    void serverStopped(int exitCode, QProcess::ExitStatus exitStatus);
    void serverErrorOccurred(QProcess::ProcessError errorType);

private:
    enum ServerState {
        Started, Starting, Stopped, Stopping, Restarting
    };

    void initAddons();
    void startAddons();
    void stopAddons();
    void deleteAddon(IMcServerAddon *addon);

    bool mFirstStart = true;

    IServerConfig *mConfig;
    bool mIsRealServer;
    ConfigGlobal::ShutdownBehavior mShutdownBehavior;
    QString mAltServer;

    QProcess mProcess;
    ServerState mState = Stopped;

    QHash<QString, IMcServerAddon *> mAddons;
};

#endif // MCSERVER_H
