#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include "interfaces/iserverconfig.h"
#include "configfunctions.h"
#include "configfilefactory.h"
#include "configfile.h"

#include <QHash>
#include <QList>
#include <QPair>

class ServerConfig : public ConfigFileFactory, public IServerConfig
{
public:
    ServerConfig(const QString &name, const QString &folderPath,
                 const QHash<QString, ConfigGlobal::ConfigData> &registeredAddons =
                 QHash<QString, ConfigGlobal::ConfigData>());

    /**
     * @brief setRegisteredAddons Sets the registered addons - this is used in initEnabledAddons()
     * and initAddonConfigs()
     * @param addons The hash of addons and their defaults
     */
    void setRegisteredAddons(const QHash<QString, ConfigGlobal::ConfigData> &addons);

    /**
     * @brief initServerConfig Creates the server config file and sets defaults
     * @param defaults The defaults to set
     */
    void initServerConfig(const ConfigGlobal::ConfigData &defaults);

    /**
     * @brief initBackupConfig Creates the backup config file and sets defaults
     * @param defaults The defaults to set
     */
    void initBackupConfig(const ConfigGlobal::ConfigData &defaults);

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
    QString getServerName() const override;
    IConfigFile *getServerConfig() override;
    IConfigFile *getBackupConfig() override;
    IConfigFile *getAddonConfig(const QString &addonName) override;

    QStringList getEnabledAddons() override;

private:
    const QString mServerName, mServerFolderPath, mAddonsFolderPath;

    ConfigFile mEnabledAddons;

    QHash<QString, ConfigGlobal::ConfigData> mRegisteredAddons;

    IConfigFile *mServerConfig = nullptr, *mBackupConfig = nullptr;
    QHash<QString, IConfigFile *> mAddonConfigs;

    static const QString SERVER_CONFIG_FILE_NAME,
                         BACKUP_CONFIG_FILE_NAME,
                         ADDON_FOLDER_NAME,
                         ENABLED_ADDONS_CONFIG_FILE_NAME;

    IConfigFile *loadFile(const QString &filePath, const ConfigGlobal::ConfigData &defaults);
    IConfigFile *createAddonConfig(const QString &addonName);
};

#endif // SERVERCONFIG_H
