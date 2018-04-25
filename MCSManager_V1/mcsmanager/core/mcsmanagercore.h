#ifndef MCSMANAGERCORE_H
#define MCSMANAGERCORE_H

#include "interfaces/imcsmanagercore.h"
#include "mcsmanager/config/interfaces/iconfigmanager.h"
#include "mcsmanager/backup/interfaces/ibackupmanager.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/interfaces/imcserverbuilder.h"

#include <QObject>
#include <QStringList>

class McsManagerCore : public IMcsManagerCore
{
public:
    McsManagerCore(IConfigManager *configManager, IBackupManager *backupManager,
                   IMcServerBuilder *serverBuilder);

    // IMcsManagerCore interface
    IMcServer *getCurrentServer() override;
    void startServer(const QString &serverName) override;
    QStringList getServerList() override;
    IServerConfig *getServerConfig(const QString &serverName) override;
    IBackupProcess *getBackupProcess(const QString &serverName) override;
    QStringList getBackupList(const QString &serverName) override;

protected:
    IConfigManager *getConfigManager() override;
    IBackupManager *getBackupManager() override;
    IMcServerBuilder *getServerBuilder() override;

private:
    IMcServer *mCurrentServer = nullptr;
    IConfigManager *mConfigManager;
    IBackupManager *mBackupManager;
    IMcServerBuilder *mServerBuilder;
};

#endif // MCSMANAGERCORE_H
