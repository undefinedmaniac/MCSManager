#ifndef IBACKUPADDONCONFIG_H
#define IBACKUPADDONCONFIG_H

class IBackupAddonConfig
{
public:
    virtual ~IBackupAddonConfig() {}

    virtual bool backupEnabled() const = 0;
    virtual bool backupOnServerStart() const = 0;
    virtual int backupPeriod() const = 0;
};

#endif // IBACKUPADDONCONFIG_H
