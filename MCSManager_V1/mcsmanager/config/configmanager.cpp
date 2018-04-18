#include "configmanager.h"

const QString ConfigManager::PRIMARY_CONFIG_NAME = QStringLiteral("config.ini"),
              ConfigManager::BACKUP_CONFIG_NAME = QStringLiteral("backup.ini"),
              ConfigManager::ADDONS_FOLDER_NAME = QStringLiteral("addons"),
              ConfigManager::ADDONS_ENABLED_CONFIG_NAME = QStringLiteral("enabled_addons.ini");

ConfigManager::ConfigManager()
{
}

void ConfigManager::registerAddon(const QString &addonName, const ConfigGlobal::ConfigData &defaults)
{
    mRegisteredAddons.insert(addonName, defaults);
}

void ConfigManager::setAppConfigDefaults(const ConfigGlobal::ConfigData &defaults)
{
    mAppDefaults = defaults;
}

void ConfigManager::setServerConfigDefaults(const ConfigGlobal::ConfigData &defaults)
{
    mServerDefaults = defaults;
}

void ConfigManager::setBackupConfigDefaults(const ConfigGlobal::ConfigData &defaults)
{
    mBackupDefaults = defaults;
}

void ConfigManager::loadConfigs(const QString &configDirectory)
{
    //Create and store the primary config file
    mAppConfig = getConfigFile(joinPaths(configDirectory, PRIMARY_CONFIG_NAME));
    mAppConfig->applyDefaults(mAppDefaults);

    QDirIterator i(configDirectory, (QDir::Dirs | QDir::NoDotAndDotDot));

    //Create a new server config for each subfolder by generating config file objects for it
    while (i.hasNext()) {
        i.next();

        ServerConfig *config = ServerConfigFactory::getServerConfig(i.filePath(), mRegisteredAddons);

        config->initServerConfig(mServerDefaults);
        config->initBackupConfig(mBackupDefaults);
        config->initEnabledAddons();
        config->initAddonConfigs();

        mServerConfigs.insert(i.fileName(), config);
    }
}

IConfigFile *ConfigManager::getAppConfig()
{
    return mAppConfig;
}

IServerConfig *ConfigManager::getServerConfig(const QString &serverName)
{
    return mServerConfigs.value(serverName, nullptr);
}

QStringList ConfigManager::getServerList() const
{
    return mServerConfigs.keys();
}
