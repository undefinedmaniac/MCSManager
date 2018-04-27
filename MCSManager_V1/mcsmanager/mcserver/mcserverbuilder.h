#ifndef MCSERVERBUILDER_H
#define MCSERVERBUILDER_H

#include "interfaces/imcserverbuilder.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "server/mcserver.h"
#include "addons/mcscp/mcscpaddon.h"
#include "addons/restarter/restarteraddon.h"
#include "addons/sleeper/sleeperaddon.h"
#include "addons/backup_service/backupserviceglobal.h"
#include "addons/backup_service/backupserviceaddon.h"

#include <QVector>

namespace Server { class McServerBuilder; }

class Server::McServerBuilder : public Server::IMcServerBuilder, public Core::McsManagerCoreChild
{
public:
    McServerBuilder(Core::IMcsManagerCore *core);

    // IMcServerBuilder interface
    Server::IMcServer *getMcServer(Config::IServerConfig *serverConfig) override;
    void deleteMcServer(Server::IMcServer *server) override;

protected:
    virtual Addon::IMcServerAddon *getAddon(const QString &name, Server::IMcServer *server);

private:
    QVector<Server::IMcServer*> mServers;
};

#endif // MCSERVERBUILDER_H
