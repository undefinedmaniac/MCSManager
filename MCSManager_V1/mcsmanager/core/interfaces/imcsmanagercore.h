#ifndef IMCSMANAGERCORE_H
#define IMCSMANAGERCORE_H

class QString;
class QStringList;
class IMcServer;
class IServerConfig;
class IBackupProcess;
class BackupList;
class IConfigManager;
class IBackupManager;
class IMcServerBuilder;

class IMcsManagerCore
{
public:
    friend class McsManagerCoreChild;

    virtual ~IMcsManagerCore() {}

    virtual IMcServer *getCurrentServer() = 0;
    virtual void startServer(const QString &serverName) = 0;
    virtual QStringList getServerList() = 0;
    virtual IServerConfig *getServerConfig(const QString &serverName) = 0;
    virtual IBackupProcess *getBackupProcess(const QString &serverName) = 0;
    virtual QStringList getBackupList(const QString &serverName) = 0;

protected:
    virtual IConfigManager *getConfigManager() = 0;
    virtual IBackupManager *getBackupManager() = 0;
    virtual IMcServerBuilder *getServerBuilder() = 0;
};

#endif // IMCSMANAGERCORE_H
