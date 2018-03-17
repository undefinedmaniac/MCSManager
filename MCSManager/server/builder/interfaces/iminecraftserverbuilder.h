#ifndef IMINECRAFTSERVERBUILDER_H
#define IMINECRAFTSERVERBUILDER_H

#include "core/mcsmanagercorebase.h"

class IServerConfig;
class IMinecraftServer;
class IMinecraftServerAddonFactory;

class IMinecraftServerBuilder : public McsManagerCoreBase
{
public:
    virtual ~IMinecraftServerBuilder() {}

    virtual IMinecraftServer *getServer(const IServerConfig *config) = 0;

    virtual void setAddonFactory(IMinecraftServerAddonFactory *factory) = 0;
    virtual IMinecraftServerAddonFactory *addonFactory() = 0;
};

#endif // IMINECRAFTSERVERBUILDER_H
