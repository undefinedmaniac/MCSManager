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

ConfigGlobal::DefaultList McServerBuilder::getAddonDefaults() const
{
    ConfigGlobal::DefaultList defaults;
    defaults.append(qMakePair(McscpConfigReader::getAddonName(), McscpConfigReader::getDefaults()));
    defaults.append(qMakePair(RestarterConfigReader::getAddonName(), RestarterConfigReader::getDefaults()));
    defaults.append(qMakePair(SleeperConfigReader::getAddonName(), SleeperConfigReader::getDefaults()));
    return defaults;
}

IMcServerAddon *McServerBuilder::getAddon(const QString &name, IMcServer *server)
{
    if (name == McscpConfigReader::getAddonName())
        return new McscpAddon(server);
    else if (name == RestarterConfigReader::getAddonName())
        return new RestarterAddon(server);
    else if (name == SleeperConfigReader::getAddonName())
        return new SleeperAddon(server);

    return nullptr;
}
