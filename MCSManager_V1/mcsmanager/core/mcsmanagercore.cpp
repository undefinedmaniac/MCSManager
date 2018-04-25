#include "mcsmanagercore.h"

McsManagerCore::McsManagerCore(IConfigManager *configManager, IBackupManager *backupManager,
                               IMcServerBuilder *serverBuilder) : mConfigManager(configManager),
    mBackupManager(backupManager), mServerBuilder(serverBuilder)
{
}

IMcServer *McsManagerCore::getCurrentServer()
{
    return mCurrentServer;
}

void McsManagerCore::startServer(const QString &serverName)
{
    if (mCurrentServer && !mCurrentServer->isRunning()) {

        if (IServerConfig *config = getServerConfig(serverName)) {
            mServerBuilder->deleteMcServer(mCurrentServer);

            mCurrentServer = mServerBuilder->getMcServer(config);
            mCurrentServer->start();
        }
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
