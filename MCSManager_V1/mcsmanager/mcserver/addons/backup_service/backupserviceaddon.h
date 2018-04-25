#ifndef BACKUPSERVICEADDON_H
#define BACKUPSERVICEADDON_H

#include "../mcserveraddonbase.h"
#include "backupserviceconfigreader.h"
#include "mcsmanager/backup/interfaces/ibackupmanager.h"
#include "mcsmanager/backup/interfaces/ibackupprocess.h"

#include <QObject>
#include <QTimer>

class BackupServiceAddon : public QObject, public McServerAddonBase
{
    Q_OBJECT
public:
    BackupServiceAddon(IMcServer *server, QObject *parent = nullptr);

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

    IBackupProcess *mProcess = nullptr;
    IMcscpAddon *mAddon = nullptr;

    QTimer mTimer;

    void runBackup();
};

#endif // BACKUPSERVICEADDON_H
