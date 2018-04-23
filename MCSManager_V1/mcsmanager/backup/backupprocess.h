#ifndef BACKUPPROCESS_H
#define BACKUPPROCESS_H

#include "mcsmanager/backup/interfaces/ibackupprocess.h"

#include <QProcess>
#include <QDateTime>

class BackupProcess : public IBackupProcess
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

private:
    QProcess mProcess;

    QStringList mSources;
    QString mDestination;
    QString mServer;
};

#endif // BACKUPPROCESS_H
