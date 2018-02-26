#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QStringList>
#include <QString>

class IServerConfig;

class IConfigManager
{
public:
    virtual ~IConfigManager() {}
    virtual void loadConfig(const QString &directory) = 0;
    virtual QStringList serverList() const = 0;
    virtual IServerConfig* getServerConfig(const QString &name) = 0;
};

#endif // ICONFIGMANAGER_H
