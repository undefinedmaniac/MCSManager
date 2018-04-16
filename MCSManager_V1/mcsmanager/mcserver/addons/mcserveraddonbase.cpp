#include "mcserveraddonbase.h"

McServerAddonBase::McServerAddonBase(const QString &name, IMcServer *server) : mName(name), mServer(server)
{
}

QString McServerAddonBase::getName() const
{
    return mName;
}

IMcServer *McServerAddonBase::getServer()
{
    return mServer;
}

IMcsManagerCore *McServerAddonBase::getCore()
{
    return mServer->getCore();
}

IConfigManager *McServerAddonBase::getConfigManager()
{
    return mServer->getConfigManager();
}

IBackupManager *McServerAddonBase::getBackupManager()
{
    return mServer->getBackupManager();
}

IMcServerBuilder *McServerAddonBase::getServerBuilder()
{
    return mServer->getServerBuilder();
}
