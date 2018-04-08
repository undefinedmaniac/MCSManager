#include "configfilefactory.h"

ConfigFileFactory::ConfigFileFactory()
{
}

ConfigFileFactory::~ConfigFileFactory()
{
    qDeleteAll(mConfigFiles);
}

IConfigFile *ConfigFileFactory::getConfigFile(const QString &filePath)
{
    IConfigFile *file = new ConfigFile(filePath);
    mConfigFiles.append(file);
    return file;
}
