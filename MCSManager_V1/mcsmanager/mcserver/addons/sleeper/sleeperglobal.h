#ifndef SLEEPERGLOBAL_H
#define SLEEPERGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace Sleeper
{

const QString ADDON_NAME = QStringLiteral("sleeper"),
              PERIOD_KEY = QStringLiteral("period"),
              SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("shutdownBehavior"),
              ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServer");

Config::ConfigData getDefaults();

}

#endif // SLEEPERGLOBAL_H
