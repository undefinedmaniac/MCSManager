#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include "iconfigfile.h"

class QStringList;
class IServerConfig;

class IConfigManager
{
public:
    virtual ~IConfigManager() {}

    //Register addons and their default values
    virtual void registerAddon(const QString &addonName, const ConfigGlobal::ConfigData &defaults) = 0;

    //Set defaults for the application and for servers
    virtual void setAppConfigDefaults(const ConfigGlobal::ConfigData &defaults) = 0;
    virtual void setServerConfigDefaults(const ConfigGlobal::ConfigData &defaults) = 0;
    virtual void setBackupConfigDefaults(const ConfigGlobal::ConfigData &defaults) = 0;

    //Search a directory and create the file structure - preload files
    virtual void loadConfigs(const QString &configDirectory) = 0;

    //Get the application configuration file object
    virtual IConfigFile *getAppConfig() = 0;

    //Get a server config object
    virtual IServerConfig *getServerConfig(const QString &serverName) = 0;

    //Get a list of available servers
    virtual QStringList getServerList() const = 0;

};

#endif // ICONFIGMANAGER_H
