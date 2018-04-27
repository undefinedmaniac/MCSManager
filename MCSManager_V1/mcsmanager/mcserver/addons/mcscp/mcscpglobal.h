#ifndef MCSCPGLOBAL_H
#define MCSCPGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace Mcscp
{

const QString ADDON_NAME = QStringLiteral("mcscp"),
              ADDRESS_KEY = QStringLiteral("address"),
              PORT_KEY = QStringLiteral("port");

Config::ConfigData getDefaults();

}

#endif // MCSCPGLOBAL_H
