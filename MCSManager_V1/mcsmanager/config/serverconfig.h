#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include "interfaces/iserverconfig.h"
#include "configfunctions.h"
#include "configfilefactory.h"
#include "configfile.h"

#include <QHash>
#include <QList>
#include <QPair>

namespace Config { class ServerConfig; }

class Config::ServerConfig : public Config::ConfigFileFactory, public Config::IServerConfig
{
public:
    ServerConfig(const QString &name, const QString &folderPath,
                 const QHash<QString, Config::ConfigData> &registeredAddons =
                 QHash<QString, Config::ConfigData>());

    /**
     * @brief setRegisteredAddons Sets the registered addons - this is used in initEnabledAddons()
     * and initAddonConfigs()
     * @param addons The hash of addons and their defaults
     */
    void setRegisteredAddons(const QHash<QString, Config::ConfigData> &addons);

    /**
     * @brief initServerConfig Creates the server config file and sets defaults
     * @param defaults The defaults to set
     */
    void initServerConfig(const Config::ConfigData &defaults);

    /**
     * @brief initBackupConfig Creates the backup config file and sets defaults
     * @param defaults The defaults to set
     */
    void initBackupConfig(const Config::ConfigData &defaults);

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
    Config::IConfigFile *getServerConfig() override;
    Config::IConfigFile *getBackupConfig() override;
    Config::IConfigFile *getAddonConfig(const QString &addonName) override;

    QStringList getEnabledAddons() override;

private:
    const QString mServerName, mServerFolderPath, mAddonsFolderPath;

    Config::ConfigFile mEnabledAddons;

    QHash<QString, Config::ConfigData> mRegisteredAddons;

    Config::IConfigFile *mServerConfig = nullptr, *mBackupConfig = nullptr;
    QHash<QString, Config::IConfigFile *> mAddonConfigs;

    static const QString SERVER_CONFIG_FILE_NAME,
                         BACKUP_CONFIG_FILE_NAME,
                         ADDON_FOLDER_NAME,
                         ENABLED_ADDONS_CONFIG_FILE_NAME;

    Config::IConfigFile *loadFile(const QString &filePath, const Config::ConfigData &defaults);
    Config::IConfigFile *createAddonConfig(const QString &addonName);
};

#endif // SERVERCONFIG_H
