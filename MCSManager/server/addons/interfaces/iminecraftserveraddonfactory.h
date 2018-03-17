#ifndef IMINECRAFTSERVERADDONFACTORY_H
#define IMINECRAFTSERVERADDONFACTORY_H

class QString;
class IMinecraftServer;
class IMinecraftServerAddon;

class IMinecraftServerAddonFactory
{
public:
    virtual ~IMinecraftServerAddonFactory() {}

    virtual IMinecraftServerAddon *getAddon(const QString &name, IMinecraftServer *server) = 0;
};

#endif // IMINECRAFTSERVERADDONFACTORY_H
