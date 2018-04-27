#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "interfaces/iconfigmanager.h"
#include "interfaces/iserverconfig.h"
#include "configfunctions.h"
#include "configfilefactory.h"
#include "serverconfigfactory.h"
#include "mcsmanager/core/mcsmanagercorechild.h"

#include <QDir>
#include <QHash>
#include <QFile>
#include <QStringList>
#include <QDirIterator>
#include <QString>

namespace Config { class ConfigManager; }

class Config::ConfigManager : public Config::ServerConfigFactory,
        public Config::ConfigFileFactory, public Core::McsManagerCoreChild, public Config::IConfigManager
{
public:
    ConfigManager(Core::IMcsManagerCore *core);

    // IConfigManager interface
    void registerAddon(const QString &addonName, const Config::ConfigData &defaults) override;

    void setAppConfigDefaults(const Config::ConfigData &defaults) override;
    void setServerConfigDefaults(const Config::ConfigData &defaults) override;
    void setBackupConfigDefaults(const Config::ConfigData &defaults) override;

    void loadConfigs(const QString &configDirectory) override;

    Config::IConfigFile *getAppConfig() override;
    Config::IServerConfig *getServerConfig(const QString &serverName) override;

    QStringList getServerList() const override;

private:
    Config::ConfigData mAppDefaults, mServerDefaults, mBackupDefaults;
    QHash<QString, Config::ConfigData> mRegisteredAddons;

    Config::IConfigFile *mAppConfig = nullptr;
    QHash<QString, Config::IServerConfig *> mServerConfigs;

    static const QString PRIMARY_CONFIG_NAME,
                         BACKUP_CONFIG_NAME,
                         ADDONS_FOLDER_NAME,
                         ADDONS_ENABLED_CONFIG_NAME;
};

#endif // CONFIGMANAGER_H
