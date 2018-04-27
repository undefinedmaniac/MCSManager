#include "mcserverbuilder.h"

using Server::McServerBuilder;

McServerBuilder::McServerBuilder(Core::IMcsManagerCore *core) : McsManagerCoreChild(core)
{
}

Server::IMcServer *McServerBuilder::getMcServer(Config::IServerConfig *serverConfig)
{
    Server::IMcServer *server = new Server::McServer(serverConfig, getCore());
    mServers.append(server);

    const QStringList enabledAddons = serverConfig->getEnabledAddons();

    foreach (const QString &addonName, enabledAddons)
        server->addAddon(getAddon(addonName, server));

    return server;
}

void McServerBuilder::deleteMcServer(Server::IMcServer *server)
{
    if (!server)
        return;

    mServers.removeOne(server);
    server->deleteLater();
}

Addon::IMcServerAddon *McServerBuilder::getAddon(const QString &name, Server::IMcServer *server)
{
    if (name == Mcscp::ADDON_NAME)
        return new Mcscp::McscpAddon(server);
    else if (name == Restarter::ADDON_NAME)
        return new Restarter::RestarterAddon(server);
    else if (name == Sleeper::ADDON_NAME)
        return new Sleeper::SleeperAddon(server);
    else if (name == BackupService::ADDON_NAME)
        return new BackupService::BackupServiceAddon(server);

    return nullptr;
}
