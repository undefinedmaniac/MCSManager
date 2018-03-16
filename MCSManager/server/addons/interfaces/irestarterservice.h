#ifndef IRESTARTERSERVICE_H
#define IRESTARTERSERVICE_H

class IRestarterAddonConfig;

class IRestarterService
{
public:
    virtual ~IRestarterService() {}

    virtual void setConfig(const IRestarterAddonConfig *config) = 0;
    virtual const IRestarterAddonConfig *config() = 0;
};

#endif // IRESTARTERSERVICE_H
