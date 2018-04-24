#ifndef IBACKUPMANAGER_H
#define IBACKUPMANAGER_H

class QString;
class IBackupProcess;
class IConfigFile;

class IBackupManager
{
public:
    virtual ~IBackupManager() {}

    virtual IBackupProcess *getBackupProcess(const QString &serverName, IConfigFile *file) = 0;
    virtual void deleteBackupProcess(IBackupProcess *process) = 0;

    virtual int secsSinceLastBackup(const QString &serverName) = 0;
};

#endif // IBACKUPMANAGER_H
