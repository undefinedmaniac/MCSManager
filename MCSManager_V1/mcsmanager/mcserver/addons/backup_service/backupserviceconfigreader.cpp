#include "backupserviceconfigreader.h"

const QString BackupServiceConfigReader::ADDON_NAME = QStringLiteral("backup_service"),
              BackupServiceConfigReader::RUN_ON_SEVER_START_KEY = QStringLiteral("runOnServerStart"),
              BackupServiceConfigReader::PERIOD_KEY = QStringLiteral("checkPeriod"),
              BackupServiceConfigReader::MINIMUM_TIME_BETWEEN_BACKUPS_KEY = QStringLiteral("minimumTimeBetweenBackups");

BackupServiceConfigReader::BackupServiceConfigReader(IConfigFile *config) : mConfig(config)
{
}

bool BackupServiceConfigReader::runOnServerStart() const
{
    return mConfig->readBool(RUN_ON_SEVER_START_KEY);
}

int BackupServiceConfigReader::period() const
{
    return mConfig->readDouble(PERIOD_KEY);
}

int BackupServiceConfigReader::minimumTimeBetweenBackups() const
{
    return mConfig->readDouble(MINIMUM_TIME_BETWEEN_BACKUPS_KEY);
}

QString BackupServiceConfigReader::getAddonName()
{
    return ADDON_NAME;
}

ConfigGlobal::ConfigData BackupServiceConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(RUN_ON_SEVER_START_KEY, QStringLiteral("true")));
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("10")));
    data.append(qMakePair(MINIMUM_TIME_BETWEEN_BACKUPS_KEY, QStringLiteral("60")));
    return data;
}
