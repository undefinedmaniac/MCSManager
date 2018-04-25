#ifndef BACKUPSERVICECONFIGREADER_H
#define BACKUPSERVICECONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"

class BackupServiceConfigReader
{
public:
    BackupServiceConfigReader(IConfigFile *config);

    bool runOnServerStart() const;
    int period() const;
    int minimumTimeBetweenBackups() const;

    static QString getAddonName();
    static ConfigGlobal::ConfigData getDefaults();

private:
    IConfigFile *mConfig;

    //BackupServiceConfigReader constants
    static const QString ADDON_NAME,
                         RUN_ON_SEVER_START_KEY,
                         PERIOD_KEY,
                         MINIMUM_TIME_BETWEEN_BACKUPS_KEY;
};

#endif // BACKUPSERVICECONFIGREADER_H
