#ifndef MINECRAFTSERVER_H
#define MINECRAFTSERVER_H

#include <QHash>
#include <QObject>
#include <QProcess>
#include <QByteArray>

#include "config/interfaces/iserverconfig.h"
#include "server/interfaces/iminecraftserver.h"
#include "server/addons/interfaces/iminecraftserveraddon.h"
#include "server/manager/interfaces/iminecraftservermanager.h"

class MinecraftServer : public QObject, public IMinecraftServer
{
    Q_OBJECT
    Q_INTERFACES(IMinecraftServer)
public:
    MinecraftServer(const IServerConfig *config);
    ~MinecraftServer();

public:
    // IMinecraftServer interface
    void setServerManager(IMinecraftServerManager *serverManager) override;
    IMinecraftServerManager *serverManager() override;

    // IMinecraftServerProcess interface
    const IServerConfig *config() const override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

    // IMinecraftServerIo interface
    QByteArray readAllStandardOutput() override;
    QByteArray readAllStandardError() override;
    int write(const QByteArray &data) override;

    // IMinecraftServerAddonManager interface
    void addAddon(IMinecraftServerAddon *addon) override;
    void removeAddon(const QString &name) override;
    QStringList addons() const override;
    IMinecraftServerAddon *getAddon(const QString &name) override;
    IMinecraftServerAddon *getAddon(const QString &name) const override;

signals:
    void started() override;
    void stopped() override;
    void error(QString errorString) override;
    void readyReadStandardOutput() override;
    void readyReadStandardError() override;
    void bytesWritten(qint64 bytes) override;

private slots:
    void errorOccurred(QProcess::ProcessError error);

private:
    QProcess mProcess;
    const IServerConfig *mConfig;
    IMinecraftServerManager *mServerManager;
    QHash<QString, IMinecraftServerAddon *> mAddons;
};

#endif // MINECRAFTSERVER_H
