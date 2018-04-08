#ifndef ISERVERCONFIG_H
#define ISERVERCONFIG_H

class QString;
class IConfigFile;
class QStringList;

class IServerConfig
{
public:
    virtual ~IServerConfig() {}

    virtual IConfigFile *getServerConfig() = 0;
    virtual IConfigFile *getBackupConfig() = 0;
    virtual IConfigFile *getAddonConfig(const QString &addonName) = 0;

    virtual QStringList getEnabledAddons() = 0;
};

#endif // ISERVERCONFIG_H
