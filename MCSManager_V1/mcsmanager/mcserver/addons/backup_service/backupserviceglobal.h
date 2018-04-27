#ifndef BACKUPSERVICEGLOBAL_H
#define BACKUPSERVICEGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace BackupService
{

const QString ADDON_NAME = QStringLiteral("backup_service"),
              RUN_ON_SEVER_START_KEY = QStringLiteral("runOnServerStart"),
              PERIOD_KEY = QStringLiteral("checkPeriod"),
              MINIMUM_TIME_BETWEEN_BACKUPS_KEY = QStringLiteral("minimumTimeBetweenBackups");

Config::ConfigData getDefaults();

}

#endif // BACKUPSERVICEGLOBAL_H
