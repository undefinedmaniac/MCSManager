#ifndef ISERVERSLEEPER_H
#define ISERVERSLEEPER_H

class ISleeperAddonConfig;

class IServerSleeper
{
public:
    virtual ~IServerSleeper() {}

    virtual const ISleeperAddonConfig *config() const = 0;

    virtual int timeUntilSleep() const = 0;
};

#endif // ISERVERSLEEPER_H
