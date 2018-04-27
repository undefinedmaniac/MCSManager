#include "mcserveraddonbase.h"

using Addon::McServerAddonBase;

McServerAddonBase::McServerAddonBase(const QString &name, Server::IMcServer *server) : mName(name), mServer(server)
{
}

QString McServerAddonBase::getName() const
{
    return mName;
}

Server::IMcServer *McServerAddonBase::getServer()
{
    return mServer;
}

Core::IMcsManagerCore *McServerAddonBase::getCore()
{
    return mServer->getCore();
}

Config::IConfigManager *McServerAddonBase::getConfigManager()
{
    return mServer->getConfigManager();
}

Backup::IBackupManager *McServerAddonBase::getBackupManager()
{
    return mServer->getBackupManager();
}

Server::IMcServerBuilder *McServerAddonBase::getServerBuilder()
{
    return mServer->getServerBuilder();
}
