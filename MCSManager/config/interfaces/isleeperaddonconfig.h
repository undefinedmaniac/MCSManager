#ifndef ISLEEPERADDONCONFIG_H
#define ISLEEPERADDONCONFIG_H

#include "iservermanagerconfig.h"

class ISleeperAddonConfig
{
public:
    virtual ~ISleeperAddonConfig() {}

    virtual bool sleeperEnabled() const = 0;
    virtual int sleeperPeriod() const = 0;
    virtual IServerManagerConfig::ShutdownBehavior sleeperShutdownBehavior() const = 0;
    virtual QString sleeperAlternativeServer() const = 0;
};

#endif // ISLEEPERADDONCONFIG_H
