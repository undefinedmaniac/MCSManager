#ifndef IMCSERVERADDON_H
#define IMCSERVERADDON_H

class QString;
class IMcServer;

class IMcServerAddon
{
public:
    virtual ~IMcServerAddon() {}

    virtual QString getName() const = 0;
    virtual IMcServer *getServer() = 0;

    virtual void preInit() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual bool isRunning() const = 0;
};

#endif // IMCSERVERADDON_H
