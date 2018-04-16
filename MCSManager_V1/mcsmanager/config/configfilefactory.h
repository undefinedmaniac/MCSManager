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
    /**
     * @brief getConfigFile Returns a new config file from the heap.
     * This new object will automatically be deleted when its associated
     * factory is deleted.
     * @param filePath The filepath for the file
     * @return The config file
     */
    virtual ConfigFile *getConfigFile(const QString &filePath);

private:
    QVector<IConfigFile *> mConfigFiles;
};

#endif // CONFIGFILEFACTORY_H
