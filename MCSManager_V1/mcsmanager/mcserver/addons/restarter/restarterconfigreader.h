#ifndef RESTARTERCONFIGREADER_H
#define RESTARTERCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"
#include "restarterglobal.h"

#include <QString>

namespace Restarter { class RestarterConfigReader; }

class Restarter::RestarterConfigReader
{
public:
    RestarterConfigReader(Config::IConfigFile *config);

    float period() const;

private:
    Config::IConfigFile *mConfig;
};

#endif // RESTARTERCONFIGREADER_H
