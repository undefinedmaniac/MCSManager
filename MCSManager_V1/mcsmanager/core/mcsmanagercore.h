#ifndef MCSMANAGERCORE_H
#define MCSMANAGERCORE_H

#include "interfaces/imcsmanagercore.h"
#include "mcsmanager/config/interfaces/iconfigmanager.h"
#include "mcsmanager/backup/interfaces/ibackupmanager.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/config/configfunctions.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/interfaces/imcserverbuilder.h"
#include "mcsmanager/backup/interfaces/ibackupmanager.h"

#include "mcsmanager/backup/backupglobal.h"
#include "mcsmanager/mcserver/server/serverglobal.h"

#include "mcsmanager/mcserver/addons/backup_service/backupserviceglobal.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"
#include "mcsmanager/mcserver/addons/restarter/restarterglobal.h"
#include "mcsmanager/mcserver/addons/sleeper/sleeperglobal.h"

#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

namespace Core { class McsManagerCore; }

class Core::McsManagerCore : public Core::IMcsManagerCore
{
    Q_OBJECT
public:
    McsManagerCore();

    void setComponents(Config::IConfigManager *configManager, Backup::IBackupManager *backupManager,
                       Server::IMcServerBuilder *serverBuilder);

    void loadConfigs(const QString &configPath);
    void startDefaultServer();

    // IMcsManagerCore interface
    Server::IMcServer *getCurrentServer() override;
    void startServer(const QString &serverName) override;
    QStringList getServerList() override;
    Config::IServerConfig *getServerConfig(const QString &serverName) override;
    Backup::IBackupProcess *getBackupProcess(const QString &serverName) override;
    QStringList getBackupList(const QString &serverName) override;

protected:
    Config::IConfigManager *getConfigManager() override;
    Backup::IBackupManager *getBackupManager() override;
    Server::IMcServerBuilder *getServerBuilder() override;

    virtual Config::ConfigData getAppDefaults() const;
    virtual Config::DefaultList getRegisteredAddons() const;

private slots:
    void startNextServer();

private:
    Server::IMcServer *mCurrentServer = nullptr;
    Config::IConfigManager *mConfigManager;
    Backup::IBackupManager *mBackupManager;
    Server::IMcServerBuilder *mServerBuilder;

    //Cache
    QString mNextServerName;

    bool checkServerName(const QString &serverName);
};

#endif // MCSMANAGERCORE_H
