#ifndef ISERVERSLEEPERCONFIG_H
#define ISERVERSLEEPERCONFIG_H

class IServerSleeperConfig
{
public:
    virtual ~IServerSleeperConfig() {}
    virtual bool enabled() const = 0;
    virtual int period() const = 0;
};

#endif // ISERVERSLEEPERCONFIG_H
