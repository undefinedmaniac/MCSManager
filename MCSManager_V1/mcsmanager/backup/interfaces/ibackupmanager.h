#ifndef IBACKUPMANAGER_H
#define IBACKUPMANAGER_H

class QString;
class QStringList;

namespace Config { class IConfigFile; }

#include <QObject>

namespace Backup
{
    class IBackupManager;
    class IBackupProcess;
}

class Backup::IBackupManager : public QObject
{
    Q_OBJECT
public:
    IBackupManager(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IBackupManager() {}

    virtual Backup::IBackupProcess *getBackupProcess(const QString &serverName, Config::IConfigFile *config) = 0;
    virtual QStringList getBackupList(Config::IConfigFile *config) = 0;

    virtual int secsSinceLastBackup(const QString &serverName) = 0;

signals:
    void backupStarted(QString server);
    void backupFinished(QString server);
    void backupError(QString server, QString errorString);
};

#endif // IBACKUPMANAGER_H
