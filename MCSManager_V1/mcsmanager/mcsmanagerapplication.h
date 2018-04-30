#ifndef MCSMANAGERAPPLICATION_H
#define MCSMANAGERAPPLICATION_H

#include "config/configmanager.h"
#include "backup/backupmanager.h"
#include "mcserver/mcserverbuilder.h"
#include "core/mcsmanagercore.h"
#include "commandline/commandline.h"

#include <QObject>
#include <QEventLoop>

namespace Application { class McsManagerApplication; }

class Application::McsManagerApplication : public QObject
{
    Q_OBJECT
public:
    McsManagerApplication(QObject *parent = nullptr);

    void start();

private slots:
    void exitApplication();

private:
    Core::McsManagerCore mCore;
    Config::ConfigManager mConfigManager;
    Backup::BackupManager mBackupManager;
    Server::McServerBuilder mServerBuilder;
    Cli::CommandLine mCommandLine;
};

#endif // MCSMANAGERAPPLICATION_H
