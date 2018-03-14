#ifndef IMINECRAFTSERVERADDONFACTORY_H
#define IMINECRAFTSERVERADDONFACTORY_H

#include <QString>

#include "server/addons/interfaces/iminecraftserveraddon.h"

class IMinecraftServerAddonFactory
{
public:
    virtual IMinecraftServerAddon *getAddon(const QString &name) = 0;
}

#endif // IMINECRAFTSERVERADDONFACTORY_H
