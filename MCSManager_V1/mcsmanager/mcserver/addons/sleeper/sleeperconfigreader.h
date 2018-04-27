#ifndef SLEEPERCONFIGREADER_H
#define SLEEPERCONFIGREADER_H

#include "sleeperglobal.h"
#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

namespace Sleeper { class SleeperConfigReader; }

class Sleeper::SleeperConfigReader
{
public:
    SleeperConfigReader(Config::IConfigFile *config);

    float period() const;
    Config::ShutdownBehavior shutdownBehavior() const;
    QString alternativeServer() const;

private:
    Config::IConfigFile *mConfig;
};

#endif // SLEEPERCONFIGREADER_H
