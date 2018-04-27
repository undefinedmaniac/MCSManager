#include "backupserviceglobal.h"

Config::ConfigData BackupService::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(RUN_ON_SEVER_START_KEY, QStringLiteral("true")));
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("10")));
    data.append(qMakePair(MINIMUM_TIME_BETWEEN_BACKUPS_KEY, QStringLiteral("60")));
    return data;
}
