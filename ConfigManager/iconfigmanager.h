#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

class QString;
class IConfigFile;
class QStringList;

struct ServerConfig;

class IConfigManager
{
public:
    virtual ~IConfigManager() {}

    virtual void registerAddon(const QString &addonName) = 0;
    virtual void loadConfiguration(const QString &configDirectory) = 0;
    virtual IConfigFile *getPrimaryConfig() = 0;
    virtual ServerConfig getServerConfig(const QString &serverName) = 0;
    virtual QStringList serverList() const = 0;
};

#endif // ICONFIGMANAGER_H
