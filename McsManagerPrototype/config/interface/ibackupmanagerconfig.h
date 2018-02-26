#ifndef IBACKUPMANAGERCONFIG_H
#define IBACKUPMANAGERCONFIG_H

#include <QStringList>
#include <QString>

class IBackupManagerConfig
{
public:
    virtual ~IBackupManagerConfig() {}
    virtual int maxBackups() const = 0;
    virtual QString destination() const = 0;
    virtual QStringList locations() const = 0;
};

#endif // IBACKUPMANAGERCONFIG_H
