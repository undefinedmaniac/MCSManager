#ifndef MCSERVERADDONBASE_H
#define MCSERVERADDONBASE_H

#include "interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/server/mcserver.h"
#include "mcsmanager/core/mcsmanagercorechild.h"

class McServerAddonBase : public IMcServerAddon
{
public:
    McServerAddonBase(const QString &name, IMcServer *server);
    virtual ~McServerAddonBase() {}

    // IMcServerAddon interface
    QString getName() const override;
    IMcServer *getServer() override;

    virtual void preInit() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;

protected:
    IMcsManagerCore *getCore();
    IConfigManager *getConfigManager();
    IBackupManager *getBackupManager();
    IMcServerBuilder *getServerBuilder();

private:
    const QString mName;
    IMcServer *mServer;
};

#endif // MCSERVERADDONBASE_H
