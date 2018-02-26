#include "configmanager.h"

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{
    qDeleteAll(mServerConfigList);
}

void ConfigManager::loadConfig(const QString &directory)
{

}

QStringList ConfigManager::serverList() const
{
    return mServerConfigList.keys();
}

IServerConfig *ConfigManager::getServerConfig(const QString &name)
{
    return mServerConfigList.value(name);
}
