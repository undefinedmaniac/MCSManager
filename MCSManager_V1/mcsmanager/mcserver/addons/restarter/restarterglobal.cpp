#include "restarterglobal.h"

Config::ConfigData Restarter::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("180")));
    return data;
}
