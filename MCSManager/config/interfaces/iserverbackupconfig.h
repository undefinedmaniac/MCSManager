#ifndef ISERVERBACKUPCONFIG_H
#define ISERVERBACKUPCONFIG_H

#include <QString>
#include <QStringList>

class IServerBackupConfig
{
public:
    virtual ~IServerBackupConfig() {}

    virtual int maxBackups() const = 0;
    virtual QString backupDestination() const = 0;
    virtual QStringList backupLocations() const = 0;
};

#endif // ISERVERBACKUPCONFIG_H
