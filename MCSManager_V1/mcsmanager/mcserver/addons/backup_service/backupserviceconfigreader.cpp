#include "backupserviceconfigreader.h"

using BackupService::BackupServiceConfigReader;

BackupServiceConfigReader::BackupServiceConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

bool BackupServiceConfigReader::runOnServerStart() const
{
    return mConfig->readBool(BackupService::RUN_ON_SEVER_START_KEY);
}

int BackupServiceConfigReader::period() const
{
    return mConfig->readDouble(BackupService::PERIOD_KEY);
}

int BackupServiceConfigReader::minimumTimeBetweenBackups() const
{
    return mConfig->readDouble(BackupService::MINIMUM_TIME_BETWEEN_BACKUPS_KEY);
}
