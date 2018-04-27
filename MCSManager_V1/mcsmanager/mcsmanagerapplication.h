#ifndef MCSMANAGERAPPLICATION_H
#define MCSMANAGERAPPLICATION_H

#include "config/configmanager.h"
#include "backup/backupmanager.h"
#include "mcserver/mcserverbuilder.h"
#include "core/mcsmanagercore.h"

namespace Application { class McsManagerApplication; }

class Application::McsManagerApplication
{
public:
    McsManagerApplication();

    void start();

private:
    Core::McsManagerCore mCore;
    Config::ConfigManager mConfigManager;
    Backup::BackupManager mBackupManager;
    Server::McServerBuilder mServerBuilder;
};

#endif // MCSMANAGERAPPLICATION_H
