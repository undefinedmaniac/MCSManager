#ifndef IMINECRAFTSERVERPROCESS_H
#define IMINECRAFTSERVERPROCESS_H

#include <QString>

class IServerConfig;

class IMinecraftServerProcess
{
public:
    virtual ~IMinecraftServerProcess() {}

    virtual const IServerConfig *config() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;

signals:
    virtual void started() = 0;
    virtual void stopped() = 0;
    virtual void error(QString errorString) = 0;

};

Q_DECLARE_INTERFACE(IMinecraftServerProcess, "IMinecraftServerProcess")

#endif // IMINECRAFTSERVERPROCESS_H
