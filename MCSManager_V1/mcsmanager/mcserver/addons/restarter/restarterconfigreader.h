#ifndef SLEEPERCONFIGREADER_H
#define SLEEPERCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QString>

class RestarterConfigReader
{
public:
    RestarterConfigReader(IConfigFile *config);

    int period() const;

    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //RestarterConfigReader defaults
    static const QString PERIOD_KEY;
};

#endif // SLEEPERCONFIGREADER_H
