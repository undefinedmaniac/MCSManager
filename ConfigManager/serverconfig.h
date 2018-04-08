#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include "iserverconfig.h"
#include "configfilefactory.h"
#include "configfile.h"
#include "configfunctions.h"

#include <QHash>
#include <QList>
#include <QPair>

class ServerConfig : public ConfigFileFactory, public IServerConfig
{
public:
    ServerConfig(const QString &folderPath, const QHash<QString, ConfigData> &addonDefaults);

    void initServerConfig(const ConfigData &defaults);
    void initBackupConfig(const ConfigData &defaults);
    void initEnabledAddons();

    // IServerConfig interface
    IConfigFile *getServerConfig() override;
    IConfigFile *getBackupConfig() override;
    IConfigFile *getAddonConfig(const QString &addonName) override;

    QStringList getEnabledAddons() override;

private:
    IConfigFile *loadFile(const QString &filePath, const ConfigData &defaults);

    IConfigFile *createAddonConfig(const QString &addonName);

    const QString mServerFolderPath, mAddonsFolderPath;

    ConfigFile mEnabledAddons;

    QHash<QString, ConfigData> mAddonDefaults;

    IConfigFile *mServerConfig = nullptr, *mBackupConfig = nullptr;
    QHash<QString, IConfigFile *> mAddonConfigs;

    static const QString SERVER_CONFIG_FILE_NAME,
                         BACKUP_CONFIG_FILE_NAME,
                         ADDON_FOLDER_NAME,
                         ENABLED_ADDONS_CONFIG_FILE_NAME;
};

#endif // SERVERCONFIG_H
