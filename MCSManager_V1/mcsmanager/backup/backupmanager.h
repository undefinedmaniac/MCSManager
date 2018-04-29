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

#include <QObject>
#include <QHash>
#include <QTime>
#include <QVector>
#include <QDebug>
#include <QDir>

namespace Backup { class BackupManager; }

class Backup::BackupManager : public Backup::IBackupManager, public Core::McsManagerCoreChild
{
    Q_OBJECT
public:
    BackupManager(Core::IMcsManagerCore *core, QObject *parent = nullptr);

    // IBackupManager interface
    Backup::IBackupProcess *getBackupProcess(const QString &serverName, Config::IConfigFile *config) override;
    QStringList getBackupList(Config::IConfigFile *config) override;

    int secsSinceLastBackup(const QString &serverName) override;

private slots:
    void processStarted();
    void processFinished();
    void processError(QString errorString);

private:
    QHash<QString, QTime> mBackupTimes;
};

#endif // BACKUPMANAGER_H
