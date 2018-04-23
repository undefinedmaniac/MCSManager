#include "backupprocess.h"

BackupProcess::BackupProcess(QObject *parent) : IBackupProcess(parent)
{
    connect(&mProcess, SIGNAL(finished(int)), SIGNAL(finished()));
    connect(&mProcess, SIGNAL(error(QProcess::ProcessError)), SIGNAL(error()));
}

void BackupProcess::setSources(const QStringList &sources)
{
    mSources = sources;
}

void BackupProcess::setDestination(const QString &destination)
{
    mDestination = destination;
}

void BackupProcess::setServer(const QString &serverName)
{
    mServer = serverName;
}

QString BackupProcess::getServer() const
{
    return mServer;
}

void BackupProcess::start()
{
    if (mSources.size() > 0 && !mDestination.isEmpty()) {
        QDateTime dateTime = QDateTime::currentDateTime();
        QDate date = dateTime.date();
        QTime time = dateTime.time();
        const QString fileName = date.toString(QStringLiteral("dd-MM-yyyy")) + '_' +
                time.toString(QStringLiteral("hh-mm-ss-a")) + QStringLiteral(".7z");

        QString destination;
        if (mDestination.endsWith('/')) {
            destination.append(mDestination);
        } else {
            destination.append(mDestination + '/');
        }
        destination.append(fileName);

        mProcess.setProgram("7za.exe");
        QStringList arguments;
        arguments.append(QChar('a'));
        arguments.append(destination);
        arguments.append(mSources);
        mProcess.setArguments(arguments);

        mProcess.start();
    }
}

bool BackupProcess::isRunning() const
{
    return mProcess.state() == QProcess::Running;
}
