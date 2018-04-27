#ifndef BACKUPSERVICEADDON_H
#define BACKUPSERVICEADDON_H

#include "backupserviceglobal.h"
#include "../mcserveraddonbase.h"
#include "backupserviceconfigreader.h"
#include "mcsmanager/backup/interfaces/ibackupmanager.h"
#include "mcsmanager/backup/interfaces/ibackupprocess.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

namespace BackupService { class BackupServiceAddon; }

class BackupService::BackupServiceAddon : public QObject, public Addon::McServerAddonBase
{
    Q_OBJECT
public:
    BackupServiceAddon(Server::IMcServer *server, QObject *parent = nullptr);

    // IMcServerAddon interface
    void preInit() override;
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void timeout();
    void backupFinished();

private:
    bool mIsRunning = false;

    bool mConfigIsValid = false;
    bool mRunOnServerStart;
    int mPeriod;
    int mMinimumTimeBetweenBackups;

    Backup::IBackupProcess *mProcess = nullptr;
    Mcscp::IMcscpAddon *mAddon = nullptr;

    QTimer mTimer;

    void runBackup();
};

#endif // BACKUPSERVICEADDON_H
