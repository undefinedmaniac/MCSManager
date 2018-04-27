#include "mcsmanagercore.h"

using Core::McsManagerCore;

McsManagerCore::McsManagerCore()
{
}

void McsManagerCore::setComponents(Config::IConfigManager *configManager, Backup::IBackupManager *backupManager,
                                   Server::IMcServerBuilder *serverBuilder)
{
    mConfigManager = configManager;
    mBackupManager = backupManager;
    mServerBuilder = serverBuilder;
}

void McsManagerCore::loadConfigs(const QString &configPath)
{
    mConfigManager->setAppConfigDefaults(getAppDefaults());
    mConfigManager->setBackupConfigDefaults(Backup::getDefaults());
    mConfigManager->setServerConfigDefaults(Server::getDefaults());

    for (const QPair<QString, Config::ConfigData> &addon : getRegisteredAddons())
        mConfigManager->registerAddon(addon.first, addon.second);

    mConfigManager->loadConfigs(configPath);
}

void McsManagerCore::startDefaultServer()
{
    Config::IConfigFile *file = mConfigManager->getAppConfig();
    const QString defaultServer = file->readString(QStringLiteral("defaultServer"));
    startServer(defaultServer);
}

Server::IMcServer *McsManagerCore::getCurrentServer()
{
    return mCurrentServer;
}

void McsManagerCore::startServer(const QString &serverName)
{
    if (!checkServerName(serverName))
        return;

    mNextServerName = serverName;

    if (mCurrentServer && mCurrentServer->isRunning()) {
        connect(mCurrentServer, SIGNAL(stopped(bool)), SLOT(startNextServer()));
        mCurrentServer->stop();
        return;
    }

    startNextServer();
}

QStringList McsManagerCore::getServerList()
{
    return mConfigManager->getServerList();
}

Config::IServerConfig *McsManagerCore::getServerConfig(const QString &serverName)
{
    return mConfigManager->getServerConfig(serverName);
}

Backup::IBackupProcess *McsManagerCore::getBackupProcess(const QString &serverName)
{
    if (!checkServerName(serverName))
        return nullptr;

    return mBackupManager->getBackupProcess(
                serverName, mConfigManager->getServerConfig(serverName)->getBackupConfig());
}

QStringList McsManagerCore::getBackupList(const QString &serverName)
{
    if (!checkServerName(serverName))
        return QStringList();

    return mBackupManager->getBackupList(mConfigManager->getServerConfig(serverName)->getBackupConfig());
}

Config::IConfigManager *McsManagerCore::getConfigManager()
{
    return mConfigManager;
}

Backup::IBackupManager *McsManagerCore::getBackupManager()
{
    return mBackupManager;
}

Server::IMcServerBuilder *McsManagerCore::getServerBuilder()
{
    return mServerBuilder;
}

Config::ConfigData McsManagerCore::getAppDefaults() const
{
    Config::ConfigData data;
    data.append(qMakePair(QStringLiteral("defaultServer"), QStringLiteral("")));
    return data;
}

Config::DefaultList McsManagerCore::getRegisteredAddons() const
{
    Config::DefaultList defaultList;
    defaultList.append(qMakePair(BackupService::ADDON_NAME, BackupService::getDefaults()));
    defaultList.append(qMakePair(Mcscp::ADDON_NAME, Mcscp::getDefaults()));
    defaultList.append(qMakePair(Restarter::ADDON_NAME, Restarter::getDefaults()));
    defaultList.append(qMakePair(Sleeper::ADDON_NAME, Sleeper::getDefaults()));
    return defaultList;
}

void McsManagerCore::startNextServer()
{
    if (Config::IServerConfig *config = getServerConfig(mNextServerName)) {
        mServerBuilder->deleteMcServer(mCurrentServer);

        mCurrentServer = mServerBuilder->getMcServer(config);
        mCurrentServer->start();
    }
}

bool McsManagerCore::checkServerName(const QString &serverName)
{
    return getServerList().contains(serverName);
}
