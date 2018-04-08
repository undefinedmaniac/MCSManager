#ifndef CONFIGFILEFACTORY_H
#define CONFIGFILEFACTORY_H

#include "configfile.h"

#include <QVector>

class ConfigFileFactory
{
public:
    ConfigFileFactory();
    virtual ~ConfigFileFactory();

protected:
    virtual IConfigFile *getConfigFile(const QString &filePath);

private:
    QVector<IConfigFile *> mConfigFiles;
};

#endif // CONFIGFILEFACTORY_H
