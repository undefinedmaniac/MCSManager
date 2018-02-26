#ifndef IBACKUPSERVICECONFIG_H
#define IBACKUPSERVICECONFIG_H

class IBackupManagerConfig;

class IBackupServiceConfig
{
public:
    virtual ~IBackupServiceConfig() {}
    virtual bool enabled() const = 0;
    virtual bool backupOnServerStart() const = 0;
    virtual int period() const = 0;
    virtual IBackupManagerConfig* backupManagerConfig() const = 0;
};

#endif // IBACKUPSERVICECONFIG_H
