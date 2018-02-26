#include "backupserviceconfig.h"

BackupServiceConfig::BackupServiceConfig(QSettings *settings) : mSettings(settings)
{
    mSettings->beginGroup(BASE_KEY);
}

bool BackupServiceConfig::enabled() const
{
    return mSettings->value(ENABLED_KEY).toBool();
}

bool BackupServiceConfig::backupOnServerStart() const
{
    return mSettings->value(BACKUP_ON_SERVER_START_KEY).toBool();
}

int BackupServiceConfig::period() const
{
    return mSettings->value(PERIOD_KEY).toInt();
}

IBackupManagerConfig *BackupServiceConfig::backupManagerConfig() const
{
    return mBackupConfig;
}
