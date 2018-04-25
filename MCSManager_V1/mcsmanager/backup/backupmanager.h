#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include "interfaces/ibackupmanager.h"
#include "mcsmanager/config/interfaces/iconfigmanager.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "backupprocess.h"
#include "backupconfigreader.h"

#include <QHash>
#include <QTime>
#include <QVector>

class BackupManager : public QObject, public IBackupManager, public McsManagerCoreChild
{
    Q_OBJECT
public:
    BackupManager(IMcsManagerCore *core);

    // IBackupManager interface
    IBackupProcess *getBackupProcess(const QString &serverName, IConfigFile *file) override;

    int secsSinceLastBackup(const QString &serverName) override;

private slots:
    void processAboutToStart();
    void processFinished();

private:
    QHash<QString, QTime> mBackupTimes;
};

#endif // BACKUPMANAGER_H
