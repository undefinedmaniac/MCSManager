#include "serverconfigfactory.h"

using Config::ServerConfigFactory;

ServerConfigFactory::ServerConfigFactory()
{
}

ServerConfigFactory::~ServerConfigFactory()
{
    qDeleteAll(mServerConfigs);
}

Config::ServerConfig *ServerConfigFactory::getServerConfig(const QString &name, const QString &folderPath,
                                                           const QHash<QString, Config::ConfigData> &registeredAddons)
{
    Config::ServerConfig *config = new Config::ServerConfig(name, folderPath, registeredAddons);
    mServerConfigs.append(config);
    return config;
}
