#include "configmanager.h"

const QString ConfigManager::GENERAL_CONFIG_NAME = QStringLiteral("GeneralConfig.ini"),
              ConfigManager::CONFIG_DIRECTORY_NAME = QStringLiteral("serverconfigs");

ConfigManager::ConfigManager() : mGeneralConfig(nullptr)
{
}

ConfigManager::~ConfigManager()
{
    qDeleteAll(getServerConfigs());
}

void ConfigManager::loadConfig(const QString &directory)
{
    if (mInitialized)
        return;

    //Create the general config object
    mGeneralConfig.reset(new GeneralConfig(joinPaths(directory, GENERAL_CONFIG_NAME)));

    //Create all the server config objects
    QDir serverConfigDirectory(joinPaths(directory, CONFIG_DIRECTORY_NAME));
    const QStringList nameFilters(QStringLiteral("*.ini"));
    const QStringList configFiles = serverConfigDirectory.entryList(nameFilters, QDir::Files);

    foreach (const QString configFile, configFiles) {

        IServerConfig *config = new ServerConfig(serverConfigDirectory.absoluteFilePath(configFile));

        const QString configName = config->name();

        if (configName == QStringLiteral(""))
            delete config;
        else
            getServerConfigs().insert(configName, config);
    }

    mInitialized = true;
}

const IGeneralConfig *ConfigManager::getGeneralConfig() const
{
    return mGeneralConfig.data();
}

QStringList ConfigManager::serverList() const
{
    return getServerConfigs().keys();
}

const IServerConfig *ConfigManager::getServerConfig(const QString &name) const
{
    return getServerConfigs().value(name, nullptr);
}

QHash<QString, IServerConfig *> &ConfigManager::getServerConfigs()
{
    return mServerConfigs;
}

const QHash<QString, IServerConfig *> &ConfigManager::getServerConfigs() const
{
    return mServerConfigs;
}

IServerConfig *ConfigManager::createServerConfig(const QString &filePath)
{
    IServerConfig *config = new ServerConfig(filePath);
    return config;
}
