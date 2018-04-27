#ifndef BACKUPPROCESS_H
#define BACKUPPROCESS_H

#include "mcsmanager/backup/interfaces/ibackupprocess.h"

#include <QProcess>
#include <QDateTime>
#include <QStringBuilder>
#include <QFile>
#include <QTimer>

namespace Backup { class BackupProcess; }

class Backup::BackupProcess : public Backup::IBackupProcess
{
    Q_OBJECT
public:
    BackupProcess(QObject *parent = nullptr);

    void setSources(const QStringList &sources);
    void setDestination(const QString &destination);
    void setServer(const QString &serverName);
    QString getServer() const;

    // IBackupProcess interface
    void start() override;
    bool isRunning() const override;

private slots:
    void stepFinished();

private:
    enum State {
        Idle, CreateTar, CreateBz2, RemoveTar
    };

    QProcess mProcess;
    State mState = Idle;

    QStringList mSources;
    QString mDestination;
    QString mServer;

    QString mDestinationTar;

    static const QString SEVEN_ZIP_EXECUTABLE;
};

#endif // BACKUPPROCESS_H
