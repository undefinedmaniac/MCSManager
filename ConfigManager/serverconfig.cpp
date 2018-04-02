#include "serverconfig.h"

ServerConfig::ServerConfig(IConfigFile *primaryConfig, IConfigFile *backupConfig,
                           QHash<QString, IConfigFile> *addonConfigs) :
    mPrimaryConfig(primaryConfig), mBackupConfig(backupConfig), mAddonConfigs(addonConfigs)
{
}

IConfigFile *ServerConfig::getPrimaryConfig()
{
    return mPrimaryConfig;
}

IConfigFile *ServerConfig::getBackupConfig()
{
    return mBackupConfig;
}

IConfigFile *ServerConfig::getAddonConfig(const QString &addonName)
{
    return mAddonConfigs->value(addonName, nullptr);
}

QStringList ServerConfig::getEnabledAddons()
{
    return mAddonConfigs->keys();
}
