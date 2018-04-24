#include "mcserverbuilder.h"

McServerBuilder::McServerBuilder(IMcsManagerCore *core) : McsManagerCoreChild(core)
{
}

IMcServer *McServerBuilder::getMcServer(IServerConfig *serverConfig)
{
    IMcServer *server = new McServer(serverConfig, getCore());
    mServers.append(server);

    const QStringList enabledAddons = serverConfig->getEnabledAddons();

    foreach (const QString &addonName, enabledAddons)
        server->addAddon(getAddon(addonName, server));

    return server;
}

void McServerBuilder::deleteMcServer(IMcServer *server)
{
    mServers.removeOne(server);
    server->deleteLater();
}

IMcServerAddon *McServerBuilder::getAddon(const QString &name, IMcServer *server)
{
    if (name == QStringLiteral("mcscp"))
        return new McscpAddon(server);
    else if (name == QStringLiteral("restarter"))
        return new RestarterAddon(server);
    else if (name == QStringLiteral("sleeper"))
        return new SleeperAddon(server);

    return nullptr;
}
