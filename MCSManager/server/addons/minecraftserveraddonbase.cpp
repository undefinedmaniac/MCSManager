#include "minecraftserveraddonbase.h"

MinecraftServerAddonBase::MinecraftServerAddonBase(const QString &name, IMinecraftServer *server) :
    mName(name), mServer(server)
{
}

IMinecraftServer *MinecraftServerAddonBase::server()
{
    return mServer;
}

QString MinecraftServerAddonBase::name() const
{
    return mName;
}
