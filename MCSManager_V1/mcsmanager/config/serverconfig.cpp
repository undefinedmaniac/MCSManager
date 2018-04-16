#include "serverconfig.h"

const QString ServerConfig::SERVER_CONFIG_FILE_NAME = QStringLiteral("config.ini"),
              ServerConfig::BACKUP_CONFIG_FILE_NAME = QStringLiteral("backup.ini"),
              ServerConfig::ADDON_FOLDER_NAME = QStringLiteral("addons"),
              ServerConfig::ENABLED_ADDONS_CONFIG_FILE_NAME = QStringLiteral("enabled_addons.ini");

ServerConfig::ServerConfig(const QString &folderPath, const QHash<QString, ConfigData> &registeredAddons) :
    mServerFolderPath(folderPath), mAddonsFolderPath(joinPaths(folderPath, ADDON_FOLDER_NAME)),
    mEnabledAddons(joinPaths(mAddonsFolderPath, ENABLED_ADDONS_CONFIG_FILE_NAME)), mRegisteredAddons(registeredAddons)
{
    mEnabledAddons.setGroup(QStringLiteral("enabled_addons"));
}

void ServerConfig::setRegisteredAddons(const QHash<QString, ConfigData> &addons)
{
    mRegisteredAddons = addons;
}

void ServerConfig::initServerConfig(const ConfigData &defaults)
{
    mServerConfig = loadFile(joinPaths(mServerFolderPath, SERVER_CONFIG_FILE_NAME), defaults);
}

void ServerConfig::initBackupConfig(const ConfigData &defaults)
{
    mBackupConfig = loadFile(joinPaths(mServerFolderPath, BACKUP_CONFIG_FILE_NAME), defaults);
}

void ServerConfig::initEnabledAddons()
{
    ConfigData enabledAddonsDefaults;

    foreach (const QString &addon, mRegisteredAddons.keys())
        enabledAddonsDefaults.append(qMakePair(addon, QStringLiteral("false")));

    mEnabledAddons.applyDefaults(enabledAddonsDefaults);
}

void ServerConfig::initAddonConfigs()
{
    foreach (const QString &addon, getEnabledAddons())
        createAddonConfig(addon);
}

IConfigFile *ServerConfig::getServerConfig()
{
    return mServerConfig;
}

IConfigFile *ServerConfig::getBackupConfig()
{
    return mBackupConfig;
}

IConfigFile *ServerConfig::getAddonConfig(const QString &addonName)
{
    IConfigFile *file = mAddonConfigs.value(addonName, nullptr);

    if (file == nullptr)
        file = createAddonConfig(addonName);

    return file;
}

QStringList ServerConfig::getEnabledAddons()
{
    QStringList enabledAddons;

    foreach (const QString &addon, mRegisteredAddons.keys()) {
        if (mEnabledAddons.readBool(addon))
            enabledAddons.append(addon);
    }

    return enabledAddons;
}

IConfigFile *ServerConfig::loadFile(const QString &filePath, const ConfigData &defaults)
{
    IConfigFile *file = getConfigFile(filePath);
    file->applyDefaults(defaults);
    return file;
}

IConfigFile *ServerConfig::createAddonConfig(const QString &addonName)
{
    const QString addonsFolderPath = joinPaths(mServerFolderPath, ADDON_FOLDER_NAME);
    const QString filePath = joinPaths(addonsFolderPath, addonName + QStringLiteral(".ini"));

    IConfigFile * file = loadFile(filePath, mRegisteredAddons.value(addonName, ConfigData()));
    mAddonConfigs.insert(addonName, file);

    return file;
}
