#ifndef MINECRAFTSERVERADDONFACTORY_H
#define MINECRAFTSERVERADDONFACTORY_H

#include "server/addons/logreader.h"
#include "server/addons/restarterservice.h"
#include "server/addons/interfaces/iminecraftserveraddonfactory.h"

class IMinecraftServer;

class MinecraftServerAddonFactory : public IMinecraftServerAddonFactory
{
public:
    MinecraftServerAddonFactory();

    // IMinecraftServerAddonFactory interface
    virtual IMinecraftServerAddon *getAddon(const QString &name, IMinecraftServer *server) override;
};

#endif // MINECRAFTSERVERADDONFACTORY_H
