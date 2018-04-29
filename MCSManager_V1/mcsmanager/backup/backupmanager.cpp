#include "backupmanager.h"

using Backup::BackupManager;

BackupManager::BackupManager(Core::IMcsManagerCore *core, QObject *parent) : IBackupManager(parent), McsManagerCoreChild(core)
{
}

Backup::IBackupProcess *BackupManager::getBackupProcess(const QString &serverName, Config::IConfigFile *config)
{
    Backup::BackupConfigReader reader(config);

    Backup::BackupProcess *process = new Backup::BackupProcess(this);
    process->setServer(serverName);
    process->setSources(reader.sources());
    process->setDestination(reader.destination());

    connect(process, SIGNAL(starting()), SLOT(processStarted()));
    connect(process, SIGNAL(finished()), SLOT(processFinished()));
    connect(process, SIGNAL(error(QString)), SLOT(processError(QString)));

    return process;
}

QStringList BackupManager::getBackupList(Config::IConfigFile *config)
{
    Backup::BackupConfigReader reader(config);
    QDir destination(reader.destination());
    return destination.entryList(QStringList(QStringLiteral(".tar.bz2")), QDir::Files | QDir::NoDotAndDotDot);
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

void BackupManager::processStarted()
{
    using Mcscp::IMcscpAddon;

    Backup::BackupProcess *process = dynamic_cast<Backup::BackupProcess*>(sender());
    Server::IMcServer *server = getCurrentServer();

    QString serverName;
    if (process)
        serverName = process->getServer();
    else
        serverName = QStringLiteral("");

    if (server && serverName == server->getName()) {
        IMcscpAddon *mcscpAddon = dynamic_cast<IMcscpAddon*>(server->getAddon(Mcscp::ADDON_NAME));
        if (mcscpAddon && mcscpAddon->isConnected())
            mcscpAddon->sendToConsole(QStringLiteral("save-all"));
    }

    emit backupStarted(serverName);
}

void BackupManager::processFinished()
{
    Backup::BackupProcess *process = dynamic_cast<Backup::BackupProcess*>(sender());

    QString serverName;
    if (process)
        serverName = process->getServer();
    else
        serverName = QStringLiteral("");

    if (!serverName.isEmpty())
        mBackupTimes.insert(serverName, QTime::currentTime());

    emit backupFinished(serverName);
}

void BackupManager::processError(QString errorString)
{
    Backup::BackupProcess *process = dynamic_cast<Backup::BackupProcess*>(sender());

    QString serverName;
    if (process)
        serverName = process->getServer();
    else
        serverName = QStringLiteral("");

    emit backupError(serverName, errorString);
}
