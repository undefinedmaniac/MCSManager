#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "iconfigmanager.h"
#include "configfunctions.h"
#include "configfilefactory.h"
#include "iserverconfig.h"
#include "serverconfigfactory.h"

#include <QDir>
#include <QHash>
#include <QFile>
#include <QStringList>
#include <QDirIterator>
#include <QString>

class ConfigManager : public ServerConfigFactory, public ConfigFileFactory, public IConfigManager
{
public:
    ConfigManager();

    // IConfigManager interface
    void registerAddon(const QString &addonName, const ConfigData &defaults) override;

    void setAppConfigDefaults(const ConfigData &defaults) override;
    void setServerConfigDefaults(const ConfigData &defaults) override;
    void setBackupConfigDefaults(const ConfigData &defaults) override;

    void loadConfigs(const QString &configDirectory) override;

    IConfigFile *getAppConfig() override;
    IServerConfig *getServerConfig(const QString &serverName) override;

    QStringList getServerList() const override;

private:
    ConfigData mAppDefaults, mServerDefaults, mBackupDefaults;
    QHash<QString, ConfigData> mRegisteredAddons;

    IConfigFile *mAppConfig = nullptr;
    QHash<QString, IServerConfig *> mServerConfigs;

    static const QString PRIMARY_CONFIG_NAME,
                         BACKUP_CONFIG_NAME,
                         ADDONS_FOLDER_NAME,
                         ADDONS_ENABLED_CONFIG_NAME;
};

#endif // CONFIGMANAGER_H
