#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QHash>
#include <QStringList>

class IConfigFile;

class ServerConfig
{
public:
    ServerConfig(IConfigFile *primaryConfig, IConfigFile *backupConfig,
                 QHash<QString, IConfigFile> *addonConfigs);

    IConfigFile *getPrimaryConfig();
    IConfigFile *getBackupConfig();
    IConfigFile *getAddonConfig(const QString &addonName);

    QStringList getEnabledAddons();

private:
    IConfigFile * const mPrimaryConfig;
    IConfigFile * const mBackupConfig;
    QHash<QString, IConfigFile *> * const mAddonConfigs;
};

#endif // SERVERCONFIG_H
