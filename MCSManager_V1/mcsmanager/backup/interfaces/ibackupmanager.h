#ifndef IBACKUPMANAGER_H
#define IBACKUPMANAGER_H

class QString;
class QStringList;

namespace Config { class IConfigFile; }

namespace Backup
{
    class IBackupManager;
    class IBackupProcess;
}

class Backup::IBackupManager
{
public:
    virtual ~IBackupManager() {}

    virtual Backup::IBackupProcess *getBackupProcess(const QString &serverName, Config::IConfigFile *config) = 0;
    virtual QStringList getBackupList(Config::IConfigFile *config);

    virtual int secsSinceLastBackup(const QString &serverName) = 0;
};

#endif // IBACKUPMANAGER_H
