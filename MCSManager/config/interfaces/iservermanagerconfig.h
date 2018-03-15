#ifndef ISERVERMANAGERCONFIG_H
#define ISERVERMANAGERCONFIG_H

class QString;

class IServerManagerConfig
{
public:
    enum ShutdownBehavior : unsigned int {
        DoNothing, RestartServer, StartAlternativeServer
    };

    virtual ~IServerManagerConfig() {}

    virtual ShutdownBehavior unexpectedShutdownBehavior() const = 0;
    virtual QString alternativeServerName() const = 0;
};

#endif // ISERVERMANAGERCONFIG_H
