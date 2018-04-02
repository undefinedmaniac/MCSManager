#include "configmanager.h"

const QString ConfigManager::PRIMARY_CONFIG_NAME = QStringLiteral("config.ini"),
              ConfigManager::BACKUP_CONFIG_NAME = QStringLiteral("backup.ini"),
              ConfigManager::ADDONS_FOLDER_NAME = QStringLiteral("addons"),
              ConfigManager::ADDONS_ENABLED_CONFIG_NAME = QStringLiteral("enabled_addons.ini");

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
    qDeleteAll(mConfigFiles);
}

void ConfigManager::registerAddon(const QString &addonName)
{
    mRegisteredAddons.append(addonName);
}

void ConfigManager::loadConfiguration(const QString &configDirectory)
{
    //Create and store the primary config file
    mPrimaryConfig = getConfigFile(joinPaths(configDirectory, PRIMARY_CONFIG_NAME));

    QDirIterator i(configDirectory, (QDir::Dirs | QDir::NoDotAndDotDot));

    //Create a new server config for each subfolder by generating config file objects for it
    while (i.hasNext()) {
        i.next();

        ServerConfig serverConfig;

        serverConfig.primary = getConfigFile(joinPaths(i.filePath(), PRIMARY_CONFIG_NAME));
        serverConfig.backup = getConfigFile(joinPaths(i.filePath(), BACKUP_CONFIG_NAME));

        const QString addonsFolderPath = joinPaths(i.filePath(), ADDONS_FOLDER_NAME);
        serverConfig.enabledAddons = getEnabledAddons(joinPaths(addonsFolderPath, ADDONS_ENABLED_CONFIG_NAME));

        mServerConfigs.insert(i.fileName(), serverConfig);
    }
}

IConfigFile *ConfigManager::getPrimaryConfig()
{
    return mPrimaryConfig;
}

ServerConfig ConfigManager::getServerConfig(const QString &serverName)
{
    return mServerConfigs.value(serverName);
}

QStringList ConfigManager::serverList() const
{
    return mServerConfigs.keys();
}

IConfigFile *ConfigManager::getConfigFile(const QString &filePath)
{
    if (!QFile::exists(filePath))
        createEmptyFile(filePath);

    IConfigFile *file = new ConfigFile(filePath);
    mConfigFiles.append(file);
    return file;
}

IEnabledAddons *ConfigManager::getEnabledAddons(const QString &filePath)
{
    EnabledAddonsConfigFile *file = new EnabledAddonsConfigFile(filePath, mRegisteredAddons);
    mConfigFiles.append(file);
    return file;
}

void ConfigManager::createEmptyFile(const QString &filePath)
{
    QFile newFile(filePath);
    newFile.open(QFile::WriteOnly);
    newFile.close();
}
