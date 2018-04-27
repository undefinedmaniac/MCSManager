#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include "interfaces/ibackupmanager.h"
#include "mcsmanager/config/interfaces/iconfigmanager.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"
#include "backupprocess.h"
#include "backupconfigreader.h"

#include <QHash>
#include <QTime>
#include <QVector>
#include <QDebug>
#include <QDir>

namespace Backup { class BackupManager; }

class Backup::BackupManager : public QObject, public Backup::IBackupManager, public Core::McsManagerCoreChild
{
    Q_OBJECT
public:
    BackupManager(Core::IMcsManagerCore *core);

    // IBackupManager interface
    Backup::IBackupProcess *getBackupProcess(const QString &serverName, Config::IConfigFile *config) override;
    QStringList getBackupList(Config::IConfigFile *config) override;

    int secsSinceLastBackup(const QString &serverName) override;

private slots:
    void processAboutToStart();
    void processFinished();

private:
    QHash<QString, QTime> mBackupTimes;
};

#endif // BACKUPMANAGER_H
