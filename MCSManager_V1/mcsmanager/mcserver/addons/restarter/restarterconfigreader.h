#ifndef RESTARTERCONFIGREADER_H
#define RESTARTERCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QString>

class RestarterConfigReader
{
public:
    RestarterConfigReader(IConfigFile *config);

    int period() const;

    static QString getAddonName();
    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //RestarterConfigReader constants
    static const QString ADDON_NAME,
                         PERIOD_KEY;
};

#endif // RESTARTERCONFIGREADER_H
