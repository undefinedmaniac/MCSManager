#ifndef ISERVERMANAGERCONFIG_H
#define ISERVERMANAGERCONFIG_H

#include <QString>

class IServerManagerConfig
{
public:
    enum ShutdownBehavior {
        DoNothing, RestartServer, StartAlternativeServer
    };

    virtual ~IServerManagerConfig() {}

    virtual ShutdownBehavior unexpectedShutdownBehavior() const = 0;
    virtual QString alternativeServerName() const = 0;
};

#endif // ISERVERMANAGERCONFIG_H
