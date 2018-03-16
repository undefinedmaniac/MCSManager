#ifndef ISERVERSLEEPER_H
#define ISERVERSLEEPER_H

class ISleeperAddonConfig;

class IServerSleeper
{
public:
    virtual ~IServerSleeper() {}

    virtual void setConfig(const ISleeperAddonConfig *config) = 0;
    virtual const ISleeperAddonConfig *config() const = 0;

    virtual int timeUntilSleep() const = 0;
    virtual void resetTimer() = 0;
};

#endif // ISERVERSLEEPER_H
