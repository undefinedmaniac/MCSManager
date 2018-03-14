#ifndef IMINECRAFTSERVERADDONMANAGER_H
#define IMINECRAFTSERVERADDONMANAGER_H

#include <QStringList>

class IMinecraftServerAddon;

class IMinecraftServerAddonManager
{
public:
    virtual ~IMinecraftServerAddonManager() {}

    virtual void addAddon(IMinecraftServerAddon *addon) = 0;
    virtual void removeAddon(const QString &name) = 0;
    virtual QStringList addons() const = 0;
    virtual IMinecraftServerAddon *getAddon(const QString &name) = 0;
    virtual IMinecraftServerAddon *getAddon(const QString &name) const  = 0;
};

#endif // IMINECRAFTSERVERADDONMANAGER_H
