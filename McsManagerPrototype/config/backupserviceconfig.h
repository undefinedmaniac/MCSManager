#ifndef BACKUPSERVICECONFIG_H
#define BACKUPSERVICECONFIG_H

#include <QString>
#include <QSettings>

#include "config/interface/ibackupserviceconfig.h"

class BackupServiceConfig : public IBackupServiceConfig
{
public:
    BackupServiceConfig(QSettings *settings);

    bool enabled() const;
    bool backupOnServerStart() const;
    int period() const;
    IBackupManagerConfig *backupManagerConfig() const;

private:
    QSettings *mSettings;

    IBackupManagerConfig *mBackupConfig;

    //CONFIG KEYS
    const QString BASE_KEY = "backup";
    const QString ENABLED_KEY = "enabled";
    const QString BACKUP_ON_SERVER_START_KEY = "backupOnServerStart";
    const QString PERIOD_KEY = "period";
};

#endif // BACKUPSERVICECONFIG_H
