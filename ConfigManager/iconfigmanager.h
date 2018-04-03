#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QHash>

class QString;
class IConfigFile;
class QStringList;

struct ServerConfig;

typedef QHash<QString, QString> ConfigHash;

class IConfigManager
{
public:
    virtual ~IConfigManager() {}

    virtual void registerAddon(const QString &addonName, const ConfigHash &defaults) = 0;
    virtual void setAppPrimaryDefaults(const ConfigHash &defaults) = 0;
    virtual void setServerPrimaryDefaults(const ConfigHash &defaults) = 0;
    virtual void setServerBackupDefaults(const ConfigHash &defaults) = 0;
    virtual void loadConfiguration() = 0;
    virtual IConfigFile *getAppConfig() = 0;
    virtual ServerConfig getServerConfig(const QString &serverName) = 0;
    virtual IConfigFile *getAddonConfig(const QString &serverName, const QString &addonName) = 0;
    virtual QStringList serverList() const = 0;
};

#endif // ICONFIGMANAGER_H
