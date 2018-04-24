#ifndef MCSMANAGERCORE_H
#define MCSMANAGERCORE_H

#include "interfaces/imcsmanagercore.h"

class McsManagerCore : public IMcsManagerCore
{
public:
    McsManagerCore();

    // IMcsManagerCore interface
    IMcServer *getCurrentServer() override;
    void startServer(const QString &serverName) override;
    QStringList getServerList() override;
    IServerConfig *getServerConfig() override;
    IBackupProcess *getBackupProcess() override;
    BackupList getBackupList(const QString &serverName) override;

protected:
    IConfigManager *getConfigManager() override;
    IBackupManager *getBackupManager() override;
    IMcServerBuilder *getServerBuilder() override;
};

#endif // MCSMANAGERCORE_H
