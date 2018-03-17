#ifndef MCSMANAGERCORE_H
#define MCSMANAGERCORE_H

#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QCoreApplication>

#include "core/interfaces/imcsmanagercore.h"
#include "core/interfaces/imcsmanagercorebase.h"

#include "config/interfaces/iserverconfig.h"
#include "config/interfaces/igeneralconfig.h"
#include "config/interfaces/iconfigmanager.h"

#include "server/interfaces/iminecraftserver.h"
#include "server/addons/interfaces/imcscpclient.h"
#include "server/builder/interfaces/iminecraftserverbuilder.h"
#include "server/manager/interfaces/iminecraftservermanager.h"
#include "server/addons/interfaces/iminecraftserveraddonfactory.h"

class McsManagerCore : public QObject, public IMcsManagerCore
{
    Q_OBJECT
    Q_INTERFACES(IMcsManagerCore)
public:
    McsManagerCore(IConfigManager *configManager, IMinecraftServerBuilder *serverBuilder,
                   IMinecraftServerAddonFactory *addonFactory, IMinecraftServerManager *serverManager);

    // IMcsManagerCore interface
    void startApplication() override;

    // IMcsManagerInterface interface
    QStringList serverList() const override;
    QStringList backupList(const QString &serverName) const override;
    const IServerConfig *getServerConfig(const QString &serverName) const override;
    void startServer(const QString &serverName) override;
    void runBackup(const QString &serverName) override;

    // ICurrentServerInterface interface
    QString name() const override;
    bool isRunning() const override;
    const IServerConfig *config() const override;
    void sendChatMsg(const QString &playerName, const QByteArray &message) override;
    void sendMcscpCmd(IMcscpCommand *cmd) override;
    QByteArray readAllLogData() const override;
    QByteArray readNewLogData() override;

signals:
    // ICurrentServerInterface interface
    void started(QString name) override;
    void stopped(QString name) override;
    void logUpdated() override;
    void event(IMcscpClient::McscpEvent event) override;

public slots:
    void stop() override;
    void forceStop() override;
    void restart() override;
    void forceRestart() override;

private:
    IConfigManager *mConfigManager;
    IMinecraftServerBuilder *mServerBuilder;
    IMinecraftServerAddonFactory *mAddonFactory;
    IMinecraftServerManager *mServerManager;
};

#endif // MCSMANAGERCORE_H
