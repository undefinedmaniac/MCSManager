#include "backupserviceaddon.h"

BackupServiceAddon::BackupServiceAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(BackupServiceConfigReader::getAddonName(), server)
{
    mTimer.setTimerType(Qt::VeryCoarseTimer);
    connect(&mTimer, SIGNAL(timeout()), SLOT(timeout()));
}

void BackupServiceAddon::preInit()
{
    BackupServiceConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mRunOnServerStart = reader.runOnServerStart();
    mPeriod = reader.period() * 60000; //Convert minutes to milliseconds
    mMinimumTimeBetweenBackups = reader.minimumTimeBetweenBackups();

    if (mPeriod > 0 && mMinimumTimeBetweenBackups >= 5)
        mConfigIsValid = true;
}

void BackupServiceAddon::init()
{
    if (mConfigIsValid) {
        if (IBackupManager *manager = getBackupManager()) {

            const QString serverName = getServer()->getName();
            IConfigFile *backupConfig = getServer()->getConfig()->getBackupConfig();

            if (IBackupProcess *process = manager->getBackupProcess(serverName, backupConfig)) {
                mTimer.setInterval(mPeriod);
                connect(process, SIGNAL(finished()), SLOT(backupFinished()));
                mProcess = process;

                mAddon = dynamic_cast<IMcscpAddon*>(getServer()->getAddon(QStringLiteral("mcscp")));
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
    timeSinceLastBackup /= 60; //Convert to minutes

    if (timeSinceLastBackup >= mMinimumTimeBetweenBackups) {

        if (mAddon && mAddon->isConnected()) {
            mAddon->broadcast(QStringLiteral("&b[Backup] Running automated server backup!"));
        }

        mProcess->start();
    }
}
