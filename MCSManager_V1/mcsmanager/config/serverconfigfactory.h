#ifndef SERVERCONFIGFACTORY_H
#define SERVERCONFIGFACTORY_H

#include "serverconfig.h"

namespace Config { class ServerConfigFactory; }

class Config::ServerConfigFactory
{
public:
    ServerConfigFactory();
    virtual ~ServerConfigFactory();

protected:
    Config::ServerConfig *getServerConfig(const QString &name, const QString &folderPath,
                                          const QHash<QString, Config::ConfigData> &registeredAddons =
                                          QHash<QString, Config::ConfigData>());

private:
    QVector<Config::IServerConfig*> mServerConfigs;
};

#endif // SERVERCONFIGFACTORY_H
