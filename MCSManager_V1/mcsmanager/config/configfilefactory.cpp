#include "configfilefactory.h"

ConfigFileFactory::ConfigFileFactory()
{
}

ConfigFileFactory::~ConfigFileFactory()
{
    qDeleteAll(mConfigFiles);
}

ConfigFile *ConfigFileFactory::getConfigFile(const QString &filePath)
{
    ConfigFile *file = new ConfigFile(filePath);
    mConfigFiles.append(file);
    return file;
}
