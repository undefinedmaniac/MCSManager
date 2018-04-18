#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "interfaces/iconfigmanager.h"
#include "interfaces/iserverconfig.h"
#include "configfunctions.h"
#include "configfilefactory.h"
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
    void registerAddon(const QString &addonName, const ConfigGlobal::ConfigData &defaults) override;

    void setAppConfigDefaults(const ConfigGlobal::ConfigData &defaults) override;
    void setServerConfigDefaults(const ConfigGlobal::ConfigData &defaults) override;
    void setBackupConfigDefaults(const ConfigGlobal::ConfigData &defaults) override;

    void loadConfigs(const QString &configDirectory) override;

    IConfigFile *getAppConfig() override;
    IServerConfig *getServerConfig(const QString &serverName) override;

    QStringList getServerList() const override;

private:
    ConfigGlobal::ConfigData mAppDefaults, mServerDefaults, mBackupDefaults;
    QHash<QString, ConfigGlobal::ConfigData> mRegisteredAddons;

    IConfigFile *mAppConfig = nullptr;
    QHash<QString, IServerConfig *> mServerConfigs;

    static const QString PRIMARY_CONFIG_NAME,
                         BACKUP_CONFIG_NAME,
                         ADDONS_FOLDER_NAME,
                         ADDONS_ENABLED_CONFIG_NAME;
};

#endif // CONFIGMANAGER_H
