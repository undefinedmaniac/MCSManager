#ifndef MCSCPCONFIGREADER_H
#define MCSCPCONFIGREADER_H

#include "mcscpglobal.h"
#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QString>

namespace Mcscp { class McscpConfigReader; }

class Mcscp::McscpConfigReader
{
public:
    McscpConfigReader(Config::IConfigFile *config);

    QString address() const;
    int port() const;

private:
    Config::IConfigFile *mConfig;
};

#endif // MCSCPCONFIGREADER_H
