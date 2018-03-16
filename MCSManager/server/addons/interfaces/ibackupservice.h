#ifndef IBACKUPSERVICE_H
#define IBACKUPSERVICE_H

class IBackupAddonConfig;

class IBackupService
{
public:
    virtual ~IBackupService() {}

    virtual void setConfig(const IBackupAddonConfig *config) = 0;
    virtual const IBackupAddonConfig *config() = 0;
};

#endif // IBACKUPSERVICE_H
