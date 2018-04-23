#include "backupmanager.h"

BackupManager::BackupManager(IMcsManagerCore *core) : McsManagerCoreChild(core)
{
}

IBackupProcess *BackupManager::getBackupProcess(const QString &serverName)
{
    if (IConfigManager *configManager = getConfigManager()) {
        if (IServerConfig *serverConfig = configManager->getServerConfig(serverName)) {
            if (IConfigFile *configFile = serverConfig->getBackupConfig()) {
                BackupConfigReader reader(configFile);

                BackupProcess *process = new BackupProcess(this);
                process->setSources(reader.sources());
                process->setDestination(reader.destination());

                connect(process, SIGNAL(finished()), SLOT(processFinished()));

                return process;
            }
        }
    }

    return nullptr;
}

int BackupManager::secsSinceLastBackup(const QString &serverName)
{
    if (mBackupTimes.contains(serverName)) {
        QTime currentTime = QTime::currentTime();
        QTime backupTime = mBackupTimes.value(serverName);
        return backupTime.secsTo(currentTime);
    }

    return -1;
}

void BackupManager::processFinished()
{
    BackupProcess *process = dynamic_cast<BackupProcess*>(sender());
    if (process)
        mBackupTimes.insert(process->getServer(), QTime::currentTime());
}
