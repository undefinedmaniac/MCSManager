#ifndef ISERVERCONFIG_H
#define ISERVERCONFIG_H

#include <QStringList>
#include <QString>

class IBackupServiceConfig;
class IMcscpClientConfig;
class IServerSleeperConfig;
class IRestarterConfig;

class IServerConfig
{
public:
    virtual ~IServerConfig() {}
    virtual QString javaPath() const = 0;
    virtual QString jarPath() const = 0;
    virtual QString workingDirectory() const = 0;
    virtual QStringList arguments() const = 0;
    virtual int unexpectedShutdownBehavior() const = 0;
    virtual IBackupServiceConfig* backupServiceConfig() const = 0;
    virtual IMcscpClientConfig* mcscpClientConfig() const = 0;
    virtual IServerSleeperConfig* serverSleeperConfig() const = 0;
    virtual IRestarterConfig* restarterConfig() const = 0;
};

#endif // ISERVERCONFIG_H
