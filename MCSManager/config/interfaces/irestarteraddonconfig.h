#ifndef IRESTARTERADDONCONFIG_H
#define IRESTARTERADDONCONFIG_H

class IRestarterAddonConfig
{
public:
    virtual bool restarterEnabled() const = 0;
    virtual int restarterPeriod() const = 0;
};

#endif // IRESTARTERADDONCONFIG_H
