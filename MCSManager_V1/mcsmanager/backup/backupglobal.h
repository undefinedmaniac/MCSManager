#ifndef BACKUPGLOBAL_H
#define BACKUPGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace Backup
{

const QString SOURCES_KEY = QStringLiteral("sources"),
              DESTINATION_KEY = QStringLiteral("destination");

Config::ConfigData getDefaults();

}

#endif // BACKUPGLOBAL_H
