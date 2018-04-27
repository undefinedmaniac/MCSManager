#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include "iconfigfile.h"

class QStringList;

namespace Config
{
    class IConfigManager;
    class IServerConfig;
    class IConfigFile;
}

class Config::IConfigManager
{
public:
    virtual ~IConfigManager() {}

    //Register addons and their default values
    virtual void registerAddon(const QString &addonName, const Config::ConfigData &defaults) = 0;

    //Set defaults for the application and for servers
    virtual void setAppConfigDefaults(const Config::ConfigData &defaults) = 0;
    virtual void setServerConfigDefaults(const Config::ConfigData &defaults) = 0;
    virtual void setBackupConfigDefaults(const Config::ConfigData &defaults) = 0;

    //Search a directory and create the file structure - preload files
    virtual void loadConfigs(const QString &configDirectory) = 0;

    //Get the application configuration file object
    virtual Config::IConfigFile *getAppConfig() = 0;

    //Get a server config object
    virtual Config::IServerConfig *getServerConfig(const QString &serverName) = 0;

    //Get a list of available servers
    virtual QStringList getServerList() const = 0;
};

#endif // ICONFIGMANAGER_H
