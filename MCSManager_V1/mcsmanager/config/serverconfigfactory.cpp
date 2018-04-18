#include "serverconfigfactory.h"

ServerConfigFactory::ServerConfigFactory()
{
}

ServerConfigFactory::~ServerConfigFactory()
{
    qDeleteAll(mServerConfigs);
}

ServerConfig *ServerConfigFactory::getServerConfig(const QString &folderPath,
                                                    const QHash<QString, ConfigGlobal::ConfigData> &registeredAddons)
{
    ServerConfig *config = new ServerConfig(folderPath, registeredAddons);
    mServerConfigs.append(config);
    return config;
}
