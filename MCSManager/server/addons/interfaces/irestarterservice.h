#ifndef IRESTARTERSERVICE_H
#define IRESTARTERSERVICE_H

class IRestarterAddonConfig;

class IRestarterService
{
public:
    virtual ~IRestarterService() {}

    virtual const IRestarterAddonConfig *config() const = 0;

    virtual int timeUntilRestart() const = 0;
};

#endif // IRESTARTERSERVICE_H
