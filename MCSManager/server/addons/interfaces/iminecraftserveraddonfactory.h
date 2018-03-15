#ifndef IMINECRAFTSERVERADDONFACTORY_H
#define IMINECRAFTSERVERADDONFACTORY_H

class QString;
class IMinecraftServerAddon;

class IMinecraftServerAddonFactory
{
public:
    virtual IMinecraftServerAddon *getAddon(const QString &name) = 0;
}

#endif // IMINECRAFTSERVERADDONFACTORY_H
