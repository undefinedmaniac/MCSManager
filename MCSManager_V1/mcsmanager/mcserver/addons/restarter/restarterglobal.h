#ifndef RESTARTERGLOBAL_H
#define RESTARTERGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace Restarter
{

const QString ADDON_NAME = QStringLiteral("restarter"),
              PERIOD_KEY = QStringLiteral("period");

Config::ConfigData getDefaults();

}

#endif // RESTARTERGLOBAL_H
