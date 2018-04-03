#include "configmanager.h"

const QString ConfigManager::PRIMARY_CONFIG_NAME = QStringLiteral("config.ini"),
              ConfigManager::BACKUP_CONFIG_NAME = QStringLiteral("backup.ini"),
              ConfigManager::ADDONS_FOLDER_NAME = QStringLiteral("addons"),
              ConfigManager::ADDONS_ENABLED_CONFIG_NAME = QStringLiteral("enabled_addons.ini");

ConfigManager::ConfigManager(const QString &configDirectory) : mConfigDirectory(configDirectory)
{
}

ConfigManager::~ConfigManager()
{
    qDeleteAll(mConfigFiles);
}

void ConfigManager::registerAddon(const QString &addonName, const ConfigHash &defaults)
{
    mRegisteredAddons.insert(addonName, defaults);
}

void ConfigManager::setAppPrimaryDefaults(const ConfigHash &defaults)
{
    mAppDefaults = defaults;
}

void ConfigManager::setServerPrimaryDefaults(const ConfigHash &defaults)
{
    mPrimaryDefaults = defaults;
}

void ConfigManager::setServerBackupDefaults(const ConfigHash &defaults)
{
    mBackupDefaults = defaults;
}

void ConfigManager::loadConfiguration()
{
    //Create and store the primary config file
    mAppConfig = getConfigFile(joinPaths(mConfigDirectory, PRIMARY_CONFIG_NAME));
    mAppConfig->applyDefaults(mAppDefaults);

    QDirIterator i(mConfigDirectory, (QDir::Dirs | QDir::NoDotAndDotDot));

    //Create a new server config for each subfolder by generating config file objects for it
    while (i.hasNext()) {
        i.next();

        PrivateServerConfig serverConfig;

        serverConfig.primary = getConfigFile(joinPaths(i.filePath(), PRIMARY_CONFIG_NAME));
        serverConfig.primary->applyDefaults(mPrimaryDefaults);

        serverConfig.backup = getConfigFile(joinPaths(i.filePath(), BACKUP_CONFIG_NAME));
        serverConfig.backup->applyDefaults(mBackupDefaults);

        const QString addonsFolderPath = joinPaths(i.filePath(), ADDONS_FOLDER_NAME);
        serverConfig.enabledAddons = getEnabledAddons(joinPaths(addonsFolderPath, ADDONS_ENABLED_CONFIG_NAME));

        //Create config files for any enabled addons
        const QStringList enabledAddons = serverConfig.enabledAddons->getEnabledAddons();

        foreach (const QString &addonName, enabledAddons) {
            IConfigFile *addonConfig = getConfigFile(joinPaths(addonsFolderPath, addonName));
            addonConfig->applyDefaults(mRegisteredAddons.value(addonName));
            serverConfig.addonConfigs.insert(addonName, addonConfig);
        }

        mServerConfigs.insert(i.fileName(), serverConfig);
    }
}

IConfigFile *ConfigManager::getAppConfig()
{
    return mAppConfig;
}

ServerConfig ConfigManager::getServerConfig(const QString &serverName)
{
    PrivateServerConfig privateServerConfig = mServerConfigs.value(serverName);

    ServerConfig serverConfig;
    serverConfig.primary = privateServerConfig.primary;
    serverConfig.backup = privateServerConfig.backup;
    serverConfig.enabledAddons = privateServerConfig.enabledAddons;
    return serverConfig;
}

IConfigFile *ConfigManager::getAddonConfig(const QString &serverName, const QString &addonName)
{
    PrivateServerConfig serverConfig = mServerConfigs.value(serverName);
    QHash<QString, IConfigFile *> *addonConfigs = &serverConfig.addonConfigs;

    if (addonConfigs->contains(addonName))
        return addonConfigs->value(addonName);

    const QString serverFolder = joinPaths(mConfigDirectory, serverName);
    const QString addonsFolder = joinPaths(serverFolder, ADDONS_FOLDER_NAME);
    const QString filePath = joinPaths(addonsFolder, addonName);

    IConfigFile *newAddonConfig = getConfigFile(filePath);
    addonConfigs->insert(addonName, newAddonConfig);
    newAddonConfig->applyDefaults(mRegisteredAddons.value(addonName));

    return newAddonConfig;
}

QStringList ConfigManager::serverList() const
{
    return mServerConfigs.keys();
}

IConfigFile *ConfigManager::getConfigFile(const QString &filePath)
{
    IConfigFile *file = new ConfigFile(filePath);
    mConfigFiles.append(file);
    return file;
}

IEnabledAddons *ConfigManager::getEnabledAddons(const QString &filePath)
{
    EnabledAddonsConfigFile *file = new EnabledAddonsConfigFile(filePath, mRegisteredAddons.keys());
    mConfigFiles.append(file);
    return file;
}
