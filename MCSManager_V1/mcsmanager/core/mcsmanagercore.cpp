#include "mcsmanagercore.h"

McsManagerCore::McsManagerCore(IConfigManager *configManager, IBackupManager *backupManager,
                               IMcServerBuilder *serverBuilder) : mConfigManager(configManager),
    mBackupManager(backupManager), mServerBuilder(serverBuilder)
{
    mConfigManager->setAppConfigDefaults(getAppDefaults());
    mConfigManager->setBackupConfigDefaults(BackupConfigReader::getDefaults());
    mConfigManager->setServerConfigDefaults(ServerConfigReader::getDefaults());

    const ConfigGlobal::DefaultList defaultList = mServerBuilder->getAddonDefaults();
    for (QPair<QString, ConfigGlobal::ConfigData> defaults : defaultList)
        mConfigManager->registerAddon(defaults.first, defaults.second);

    mConfigManager->loadConfigs(joinPaths(QCoreApplication::applicationDirPath(), QStringLiteral("config")));
}

IMcServer *McsManagerCore::getCurrentServer()
{
    return mCurrentServer;
}

void McsManagerCore::startServer(const QString &serverName)
{
    if (getServerList().contains(serverName)) {
        mNextServerName = serverName;

        if (mCurrentServer) {
            if (mCurrentServer->isRunning()) {
                connect(mCurrentServer, SIGNAL(stopped(bool)), SLOT(waitForServerStop()));
                mCurrentServer->stop();
                return;
            }
        }

        startNextServer();
    }
}

QStringList McsManagerCore::getServerList()
{
    return mConfigManager->getServerList();
}

IServerConfig *McsManagerCore::getServerConfig(const QString &serverName)
{
    return mConfigManager->getServerConfig(serverName);
}

IBackupProcess *McsManagerCore::getBackupProcess(const QString &serverName)
{
    return mBackupManager->getBackupProcess(
                serverName, mConfigManager->getServerConfig(serverName)->getBackupConfig());
}

QStringList McsManagerCore::getBackupList(const QString &serverName)
{

}

IConfigManager *McsManagerCore::getConfigManager()
{
    return mConfigManager;
}

IBackupManager *McsManagerCore::getBackupManager()
{
    return mBackupManager;
}

IMcServerBuilder *McsManagerCore::getServerBuilder()
{
    return mServerBuilder;
}

ConfigGlobal::ConfigData McsManagerCore::getAppDefaults() const
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(QStringLiteral("defaultServer"), QStringLiteral("")));
    return data;
}

void McsManagerCore::startNextServer()
{
    if (IServerConfig *config = getServerConfig(mNextServerName)) {
        mServerBuilder->deleteMcServer(mCurrentServer);

        mCurrentServer = mServerBuilder->getMcServer(config);
        mCurrentServer->start();
    }
}
