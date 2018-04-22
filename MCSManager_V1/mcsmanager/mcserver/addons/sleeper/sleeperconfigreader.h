#ifndef SLEEPERCONFIGREADER_H
#define SLEEPERCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

class SleeperConfigReader
{
public:
    SleeperConfigReader(IConfigFile *config);

    int period() const;
    ConfigGlobal::ShutdownBehavior shutdownBehavior() const;
    QString alternativeServer() const;

    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //SleeperConfigReader defaults
    static const QString PERIOD_KEY,
                         SHUTDOWN_BEHAVIOR_KEY,
                         ALTERNATIVE_SERVER_KEY;
};

#endif // SLEEPERCONFIGREADER_H
