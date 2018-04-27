#include "sleeperglobal.h"

Config::ConfigData Sleeper::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("60")));
    data.append(qMakePair(SHUTDOWN_BEHAVIOR_KEY, QStringLiteral("DoNothing")));
    data.append(qMakePair(ALTERNATIVE_SERVER_KEY, QStringLiteral("")));
    return data;
}
