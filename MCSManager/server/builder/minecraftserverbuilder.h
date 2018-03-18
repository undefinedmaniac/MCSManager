#ifndef MINECRAFTSERVERBUILDER_H
#define MINECRAFTSERVERBUILDER_H

#include <QScopedPointer>

#include "server/minecraftserver.h"
#include "server/interfaces/iminecraftserver.h"
#include "server/builder/interfaces/iminecraftserverbuilder.h"
#include "server/addons/interfaces/iminecraftserveraddonfactory.h"

class MinecraftServerBuilder : public IMinecraftServerBuilder
{
public:
    MinecraftServerBuilder(IMinecraftServerAddonFactory *factory = nullptr);
    ~MinecraftServerBuilder();

    // IMinecraftServerBuilder interface
    IMinecraftServer *getServer(const IServerConfig *config) override;
    void setAddonFactory(IMinecraftServerAddonFactory *factory) override;
    IMinecraftServerAddonFactory *addonFactory() override;

private:
    IMinecraftServer *mServer = nullptr;
    IMinecraftServerAddonFactory *mFactory;

    void deleteServer();
};

#endif // MINECRAFTSERVERBUILDER_H
