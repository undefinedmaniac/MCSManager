#include "configfilefactory.h"

using Config::ConfigFileFactory;

ConfigFileFactory::ConfigFileFactory()
{
}

ConfigFileFactory::~ConfigFileFactory()
{
    qDeleteAll(mConfigFiles);
}

Config::ConfigFile *ConfigFileFactory::getConfigFile(const QString &filePath)
{
    Config::ConfigFile *file = new Config::ConfigFile(filePath);
    mConfigFiles.append(file);
    return file;
}
