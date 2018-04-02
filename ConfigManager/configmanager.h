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

struct ServerConfig {
    IConfigFile *primary;
    IConfigFile *backup;
    IEnabledAddons *enabledAddons;
};

class ConfigManager : IConfigManager
{
public:
    ConfigManager();
    virtual ~ConfigManager();

    // IConfigManager interface
    void registerAddon(const QString &addonName) override;
    void loadConfiguration(const QString &configDirectory) override;
    IConfigFile *getPrimaryConfig() override;
    ServerConfig getServerConfig(const QString &serverName) override;
    QStringList serverList() const override;

protected:
    virtual IConfigFile *getConfigFile(const QString &filePath);
    virtual IEnabledAddons *getEnabledAddons(const QString &filePath);

private:
    IConfigFile *mPrimaryConfig = nullptr;
    QHash<QString, ServerConfig> mServerConfigs;
    QVector<IConfigFile *> mConfigFiles;
    QStringList mRegisteredAddons;

    void createEmptyFile(const QString &filePath);

    static const QString PRIMARY_CONFIG_NAME,
                         BACKUP_CONFIG_NAME,
                         ADDONS_FOLDER_NAME,
                         ADDONS_ENABLED_CONFIG_NAME;
};

#endif // CONFIGMANAGER_H
