#ifndef MINECRAFTSERVERADDONBASE_H
#define MINECRAFTSERVERADDONBASE_H

#include <QString>

#include "server/addons/interfaces/iminecraftserveraddon.h"

class MinecraftServerAddonBase : public IMinecraftServerAddon
{
public:
    MinecraftServerAddonBase(const QString &name, IMinecraftServer *server);
    virtual ~MinecraftServerAddonBase() {}

    // IMinecraftServerAddon interface
    IMinecraftServer *server() override;
    IMinecraftServer *server() const override;
    QString name() const override;

private:
    const QString mName;
    IMinecraftServer *mServer;
};

#endif // MINECRAFTSERVERADDONBASE_H

