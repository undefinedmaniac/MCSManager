#ifndef MCSERVERBUILDER_H
#define MCSERVERBUILDER_H

#include "interfaces/imcserverbuilder.h"
#include "mcsmanager/core/mcsmanagercorechild.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "server/mcserver.h"
#include "addons/mcscp/mcscpaddon.h"
#include "addons/restarter/restarteraddon.h"
#include "addons/sleeper/sleeperaddon.h"

#include <QVector>

class McServerBuilder : public IMcServerBuilder, public McsManagerCoreChild
{
public:
    McServerBuilder();

    // IMcServerBuilder interface
    IMcServer *getMcServer(IServerConfig *serverConfig) override;
    void deleteMcServer(IMcServer *server) override;

protected:
    virtual IMcServerAddon *getAddon(const QString &name, IMcServer *server);

private:
    QVector<IMcServer*> mServers;
};

#endif // MCSERVERBUILDER_H
