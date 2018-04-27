#ifndef IMCSERVERADDON_H
#define IMCSERVERADDON_H

class QString;

namespace Server { class IMcServer; }

namespace Addon { class IMcServerAddon; }

class Addon::IMcServerAddon
{
public:
    virtual ~IMcServerAddon() {}

    virtual QString getName() const = 0;
    virtual Server::IMcServer *getServer() = 0;

    virtual void preInit() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual bool isRunning() const = 0;
};

#endif // IMCSERVERADDON_H
