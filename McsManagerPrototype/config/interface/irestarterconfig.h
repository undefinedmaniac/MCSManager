#ifndef IRESTARTERCONFIG_H
#define IRESTARTERCONFIG_H

class IRestarterConfig
{
public:
    virtual ~IRestarterConfig() {}
    virtual bool enabled() const = 0;
    virtual int period() const = 0;
};

#endif // IRESTARTERCONFIG_H
