#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QHash>

#include "config/interface/iconfigmanager.h"
#include "config/interface/iserverconfig.h"

class ConfigManager : public IConfigManager
{
public:
    ConfigManager();
    ~ConfigManager();

    void loadConfig(const QString &directory);
    QStringList serverList() const;
    IServerConfig *getServerConfig(const QString &name);

private:
    QHash<QString, IServerConfig*> mServerConfigList;
};

#endif // CONFIGMANAGER_H
