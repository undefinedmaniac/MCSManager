#ifndef IMINECRAFTSERVERADDON_H
#define IMINECRAFTSERVERADDON_H

class QString;
class IMinecraftServer;

class IMinecraftServerAddon
{
public:
    virtual ~IMinecraftServerAddon() {}

    virtual IMinecraftServer *server() = 0;
    virtual IMinecraftServer *server() const = 0;
    virtual QString name() const = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
};

#endif // IMINECRAFTSERVERADDON_H
