#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include "configfunctions.h"
#include "iserverconfig.h"
#include "configfilefactory.h"
#include "configfile.h"

#include <QHash>
#include <QList>
#include <QPair>

class ServerConfig : public ConfigFileFactory, public IServerConfig
{
public:
    ServerConfig(const QString &folderPath, const QHash<QString, ConfigData> &registeredAddons =
            QHash<QString, ConfigData>());

    /**
     * @brief setRegisteredAddons Sets the registered addons - this is used in initEnabledAddons()
     * and initAddonConfigs()
     * @param addons The hash of addons and their defaults
     */
    void setRegisteredAddons(const QHash<QString, ConfigData> &addons);

    /**
     * @brief initServerConfig Creates the server config file and sets defaults
     * @param defaults The defaults to set
     */
    void initServerConfig(const ConfigData &defaults);

    /**
     * @brief initBackupConfig Creates the backup config file and sets defaults
     * @param defaults The defaults to set
     */
    void initBackupConfig(const ConfigData &defaults);

    /**
     * @brief initEnabledAddons Creates the enabled addons config file. This
     * will only be useful if setRegisteredAddons() was previously called, otherwise
     * the default file will be blank.
     */
    void initEnabledAddons();

    /**
     * @brief initAddonConfigs Creates config files for each of the enabled addons
     * and sets their defaults. This only works after setRegisteredAddons() and
     * initEnabledAddons() has been called.
     */
    void initAddonConfigs();

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

    QHash<QString, ConfigData> mRegisteredAddons;

    IConfigFile *mServerConfig = nullptr, *mBackupConfig = nullptr;
    QHash<QString, IConfigFile *> mAddonConfigs;

    static const QString SERVER_CONFIG_FILE_NAME,
                         BACKUP_CONFIG_FILE_NAME,
                         ADDON_FOLDER_NAME,
                         ENABLED_ADDONS_CONFIG_FILE_NAME;
};

#endif // SERVERCONFIG_H
