#include "backupprocess.h"

using Backup::BackupProcess;

#ifdef Q_OS_WIN
    const QString BackupProcess::SEVEN_ZIP_EXECUTABLE = QStringLiteral("7za.exe");
#elif Q_OS_LINUX
    const QString BackupProcess::SEVEN_ZIP_EXECUTABLE = QStringLiteral("");
#else
    const QString BackupProcess::SEVEN_ZIP_EXECUTABLE = QStringLiteral("");
#endif

BackupProcess::BackupProcess(QObject *parent) : IBackupProcess(parent)
{
    connect(&mProcess, SIGNAL(finished(int)), SLOT(stepFinished()));
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
        emit aboutToStart();
        mState = CreateTar;
        QTimer::singleShot(2000, this, SLOT(stepFinished()));
    }
}

bool BackupProcess::isRunning() const
{
    return mProcess.state() == QProcess::Running;
}

void BackupProcess::stepFinished()
{
    switch (mState) {
    case CreateTar: {
        QDateTime dateTime = QDateTime::currentDateTime();
        QDate date = dateTime.date();
        QTime time = dateTime.time();
        const QString fileName = date.toString(QStringLiteral("MM-dd-yyyy")) % '_' %
                time.toString(QStringLiteral("hh-mm-ss-a")) % QStringLiteral(".tar");

        mDestinationTar += mDestination;

        if (!mDestinationTar.endsWith('/'))
            mDestinationTar += '/';

        mDestinationTar += fileName;

        QStringList arguments;
        arguments.reserve(3);
        arguments << QChar('a') << mDestinationTar << mSources;

        mState = CreateBz2;
        mProcess.start(SEVEN_ZIP_EXECUTABLE, arguments);
        break;
    }
    case CreateBz2: {
        QStringList arguments;
        arguments.reserve(3);
        arguments << QChar('a') << mDestinationTar % QStringLiteral(".bz2") << mDestinationTar;

        mState = RemoveTar;
        mProcess.start(SEVEN_ZIP_EXECUTABLE, arguments);
        break;
    }
    case RemoveTar: {
        QFile::remove(mDestinationTar);

        mState = Idle;
        mDestinationTar.clear();

        emit finished();
        break;
    }
    default:
        break;
    }
}
