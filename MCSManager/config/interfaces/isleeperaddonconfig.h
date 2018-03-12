#ifndef ISLEEPERADDONCONFIG_H
#define ISLEEPERADDONCONFIG_H

class ISleeperAddonConfig
{
public:
    virtual bool sleeperEnabled() const = 0;
    virtual int sleeperPeriod() const = 0;
};

#endif // ISLEEPERADDONCONFIG_H
