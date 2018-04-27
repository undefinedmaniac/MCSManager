#include "backupmanager.h"

using Backup::BackupManager;

BackupManager::BackupManager(Core::IMcsManagerCore *core) : McsManagerCoreChild(core)
{
}

Backup::IBackupProcess *BackupManager::getBackupProcess(const QString &serverName, Config::IConfigFile *config)
{    
    Backup::BackupConfigReader reader(config);

    Backup::BackupProcess *process = new Backup::BackupProcess(this);
    process->setServer(serverName);
    process->setSources(reader.sources());
    process->setDestination(reader.destination());

    connect(process, SIGNAL(aboutToStart()), SLOT(processAboutToStart()));
    connect(process, SIGNAL(finished()), SLOT(processFinished()));

    return process;
}

QStringList BackupManager::getBackupList(Config::IConfigFile *config)
{
    Backup::BackupConfigReader reader(config);
    QDir destination(reader.destination(), QStringLiteral(".tar.bz2"), filter = QDir::Dirs | QDir::NoDotAndDotDot);
    return destination.entryList();
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

void BackupManager::processAboutToStart()
{
    using Mcscp::IMcscpAddon;

    qDebug() << "Process about to start!";

    Backup::BackupProcess *process = dynamic_cast<Backup::BackupProcess*>(sender());
    Server::IMcServer *server = getCurrentServer();

    if (process && server && process->getServer() == server->getName()) {
        qDebug() << "Sending save-all";
        IMcscpAddon *mcscpAddon = dynamic_cast<IMcscpAddon*>(server->getAddon(Mcscp::ADDON_NAME));
        if (mcscpAddon && mcscpAddon->isConnected())
            mcscpAddon->sendToConsole(QStringLiteral("save-all"));
    }
}

void BackupManager::processFinished()
{
    Backup::BackupProcess *process = dynamic_cast<Backup::BackupProcess*>(sender());
    if (process)
        mBackupTimes.insert(process->getServer(), QTime::currentTime());
}
