#ifndef BACKUPSERVICECONFIGREADER_H
#define BACKUPSERVICECONFIGREADER_H

#include "backupserviceglobal.h"
#include "mcsmanager/config/interfaces/iconfigfile.h"

namespace BackupService { class BackupServiceConfigReader; }

class BackupService::BackupServiceConfigReader
{
public:
    BackupServiceConfigReader(Config::IConfigFile *config);

    bool runOnServerStart() const;
    int period() const;
    int minimumTimeBetweenBackups() const;

private:
    Config::IConfigFile *mConfig;
};

#endif // BACKUPSERVICECONFIGREADER_H
