#ifndef MCSERVERADDONBASE_H
#define MCSERVERADDONBASE_H

#include "interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/core/mcsmanagercorechild.h"

namespace Addon { class McServerAddonBase; }

class Addon::McServerAddonBase : public Addon::IMcServerAddon
{
public:
    McServerAddonBase(const QString &name, Server::IMcServer *server);
    virtual ~McServerAddonBase() {}

    // IMcServerAddon interface
    QString getName() const override;
    Server::IMcServer *getServer() override;

    virtual void preInit() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;

protected:
    Core::IMcsManagerCore *getCore();
    Config::IConfigManager *getConfigManager();
    Backup::IBackupManager *getBackupManager();
    Server::IMcServerBuilder *getServerBuilder();

private:
    const QString mName;
    Server::IMcServer *mServer;
};

#endif // MCSERVERADDONBASE_H
