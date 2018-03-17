#ifndef IBACKUPSERVICE_H
#define IBACKUPSERVICE_H

class IBackupAddonConfig;

class IBackupService
{
public:
    virtual ~IBackupService() {}

    virtual const IBackupAddonConfig *config() const = 0;
};

#endif // IBACKUPSERVICE_H
