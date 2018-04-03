#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "iconfigmanager.h"
#include "configfunctions.h"
#include "configfile.h"
#include "enabledaddonsconfigfile.h"

#include <QDir>
#include <QHash>
#include <QFile>
#include <QStringList>
#include <QDirIterator>
#include <QString>

class ConfigManager;

struct ServerConfig {
    IConfigFile *primary;
    IConfigFile *backup;
    IEnabledAddons *enabledAddons;
};

class ConfigManager : IConfigManager
{
public:
    ConfigManager(const QString &configDirectory);
    virtual ~ConfigManager();

    // IConfigManager interface
    void registerAddon(const QString &addonName, const ConfigHash &defaults) override;
    void setAppPrimaryDefaults(const ConfigHash &defaults) override;
    void setServerPrimaryDefaults(const ConfigHash &defaults) override;
    void setServerBackupDefaults(const ConfigHash &defaults) override;
    void loadConfiguration() override;
    IConfigFile *getAppConfig() override;
    ServerConfig getServerConfig(const QString &serverName) override;
    IConfigFile *getAddonConfig(const QString &serverName, const QString &addonName) override;
    QStringList serverList() const override;

protected:
    virtual IConfigFile *getConfigFile(const QString &filePath);
    virtual IEnabledAddons *getEnabledAddons(const QString &filePath);

private:
    struct PrivateServerConfig {
        IConfigFile *primary;
        IConfigFile *backup;
        IEnabledAddons *enabledAddons;
        QHash<QString, IConfigFile *> addonConfigs;
    };

    const QString mConfigDirectory;

    ConfigHash mAppDefaults;
    ConfigHash mPrimaryDefaults;
    ConfigHash mBackupDefaults;

    IConfigFile *mAppConfig = nullptr;
    QHash<QString, PrivateServerConfig> mServerConfigs;

    QHash<QString, ConfigHash> mRegisteredAddons;

    QVector<IConfigFile *> mConfigFiles;

    static const QString PRIMARY_CONFIG_NAME,
                         BACKUP_CONFIG_NAME,
                         ADDONS_FOLDER_NAME,
                         ADDONS_ENABLED_CONFIG_NAME;
};

#endif // CONFIGMANAGER_H
