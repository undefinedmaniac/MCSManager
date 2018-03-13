#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H

#include <QString>

#include "igeneralconfig.h"
#include "iserverconfig.h"

class IConfigManager
{
public:
    virtual ~IConfigManager() {}

    virtual void loadConfig(const QString &directory) = 0;

    virtual const IGeneralConfig *getGeneralConfig() const = 0;

    virtual QStringList serverList() const = 0;
    virtual const IServerConfig *getServerConfig(const QString &name) const = 0;
};

#endif // ICONFIGMANAGER_H
