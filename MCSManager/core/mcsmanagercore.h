#ifndef MCSMANAGERCORE_H
#define MCSMANAGERCORE_H

#include <QObject>

#include "core/interfaces/imcsmanagercore.h"

class McsManagerCore : public QObject, public IMcsManagerCore
{
    Q_OBJECT
    Q_INTERFACES(IMcsManagerCore)
public:
    McsManagerCore();

    // IMcsManagerCore interface
    void startApplication() override;

    // IMcsManagerInterface interface
    QStringList serverList() const override;
    QStringList backupList(const QString &serverName) const override;
    IServerConfig *getServerConfig(const QString &serverName) const override;
    void startServer(const QString &serverName) override;
    void runBackup(const QString &serverName) override;

    // ICurrentServerInterface interface
    QString name() const override;
    const IServerConfig *config() const override;
    void sendChatMsg(const QString &playerName, const QByteArray &message) override;
    void sendMcscpCmd(IMcscpCommand *cmd) override;
    void stop() override;
    void forceStop() override;
    void restart() override;
    void forceRestart() override;
    QByteArray readAllLogData() const override;
    QByteArray readNewLogData() override;

signals:
    // ICurrentServerInterface interface
    void started(QString name) override;
    void stopped(QString name) override;
    void logUpdated() override;
    void event(QString event) override;
};

#endif // MCSMANAGERCORE_H
