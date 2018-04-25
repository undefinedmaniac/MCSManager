#ifndef MCSCPCONFIGREADER_H
#define MCSCPCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QString>

class McscpConfigReader
{
public:
    McscpConfigReader(IConfigFile *config);

    QString address() const;
    int port() const;

    static QString getAddonName();
    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //McscpConfigReader constants
    static const QString ADDON_NAME,
                         ADDRESS_KEY,
                         PORT_KEY;
};

#endif // MCSCPCONFIGREADER_H
