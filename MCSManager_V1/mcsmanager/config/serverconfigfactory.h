#ifndef SERVERCONFIGFACTORY_H
#define SERVERCONFIGFACTORY_H

#include "serverconfig.h"

class ServerConfigFactory
{
public:
    ServerConfigFactory();
    virtual ~ServerConfigFactory();

protected:
    ServerConfig *getServerConfig(const QString &folderPath, const QHash<QString, ConfigData> &registeredAddons =
            QHash<QString, ConfigData>());

private:
    QVector<IServerConfig *> mServerConfigs;
};

#endif // SERVERCONFIGFACTORY_H
