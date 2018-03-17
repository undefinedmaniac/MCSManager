#include "minecraftserveraddonfactory.h"

MinecraftServerAddonFactory::MinecraftServerAddonFactory()
{

}

IMinecraftServerAddon *MinecraftServerAddonFactory::getAddon(const QString &name, IMinecraftServer *server)
{
    if (name == QStringLiteral("logReader"))
        return new LogReader(name, server);
    else if (name == QStringLiteral("restarter"))
        return new RestarterService(name, server);

    return nullptr;
}
