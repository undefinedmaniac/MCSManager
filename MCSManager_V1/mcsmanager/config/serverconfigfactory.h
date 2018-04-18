#ifndef SERVERCONFIGFACTORY_H
#define SERVERCONFIGFACTORY_H

#include "serverconfig.h"

class ServerConfigFactory
{
public:
    ServerConfigFactory();
    virtual ~ServerConfigFactory();

protected:
    ServerConfig *getServerConfig(const QString &folderPath, const QHash<QString, ConfigGlobal::ConfigData> &registeredAddons =
            QHash<QString, ConfigGlobal::ConfigData>());

private:
    QVector<IServerConfig *> mServerConfigs;
};

#endif // SERVERCONFIGFACTORY_H
