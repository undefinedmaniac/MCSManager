#include "backupserviceaddon.h"

using BackupService::BackupServiceAddon;

BackupServiceAddon::BackupServiceAddon(Server::IMcServer *server, QObject *parent) :
    QObject(parent), Addon::McServerAddonBase(BackupService::ADDON_NAME, server)
{
    mTimer.setTimerType(Qt::VeryCoarseTimer);
    connect(&mTimer, SIGNAL(timeout()), SLOT(timeout()));
}

void BackupServiceAddon::preInit()
{
    BackupService::BackupServiceConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mRunOnServerStart = reader.runOnServerStart();
    mPeriod = reader.period() * 60000; //Convert minutes to milliseconds
    mMinimumTimeBetweenBackups = reader.minimumTimeBetweenBackups();

    if (mPeriod > 0 && mMinimumTimeBetweenBackups >= 5)
        mConfigIsValid = true;
}

void BackupServiceAddon::init()
{
    if (mConfigIsValid) {
        if (Backup::IBackupManager *manager = getBackupManager()) {

            const QString serverName = getServer()->getName();
            Config::IConfigFile *backupConfig = getServer()->getConfig()->getBackupConfig();

            if (Backup::IBackupProcess *process = manager->getBackupProcess(serverName, backupConfig)) {
                mTimer.setInterval(mPeriod);
                connect(process, SIGNAL(finished()), SLOT(backupFinished()));
                mProcess = process;

                mAddon = dynamic_cast<Mcscp::IMcscpAddon*>(getServer()->getAddon(QStringLiteral("mcscp")));
            }
        }
    }
}

void BackupServiceAddon::start()
{
    if (mConfigIsValid && mProcess) {
        mIsRunning = true;

        if (mRunOnServerStart)
            runBackup();

        mTimer.start();
    }
}

void BackupServiceAddon::stop()
{
    mIsRunning = false;
    mTimer.stop();
}

bool BackupServiceAddon::isRunning() const
{
    return mIsRunning;
}

void BackupServiceAddon::timeout()
{
    runBackup();
}

void BackupServiceAddon::backupFinished()
{
    if (mAddon && mAddon->isConnected()) {
        mAddon->broadcast(QStringLiteral("&b[Backup] Server backup complete!"));
    }
}

void BackupServiceAddon::runBackup()
{
    int timeSinceLastBackup = getBackupManager()->secsSinceLastBackup(getServer()->getName());

    if (timeSinceLastBackup == -1 || timeSinceLastBackup / 60 >= mMinimumTimeBetweenBackups) {

        if (mAddon && mAddon->isConnected()) {
            mAddon->broadcast(QStringLiteral("&b[Backup] Running automated server backup!"));
        }

        mProcess->start();
    }
}
