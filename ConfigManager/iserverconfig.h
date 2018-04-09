#ifndef ISERVERCONFIG_H
#define ISERVERCONFIG_H

class QString;
class IConfigFile;
class QStringList;

class IServerConfig
{
public:
    virtual ~IServerConfig() {}

    /**
     * @brief getServerConfig Gets the server config file
     * @return The server config if available, otherwise nullptr
     */
    virtual IConfigFile *getServerConfig() = 0;

    /**
     * @brief getBackupConfig Gets the backup config file
     * @return The backup config if available, otherwise nullptr
     */
    virtual IConfigFile *getBackupConfig() = 0;

    /**
     * @brief getAddonConfig Gets an addon config file
     * @param addonName The addon name
     * @return The addon config if available, otherwise nullptr
     */
    virtual IConfigFile *getAddonConfig(const QString &addonName) = 0;

    /**
     * @brief getEnabledAddons Gets a list of the enabled addons
     * @return The list of enabled addons
     */
    virtual QStringList getEnabledAddons() = 0;
};

#endif // ISERVERCONFIG_H
