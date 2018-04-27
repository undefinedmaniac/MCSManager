#include "mcsmanagercorechild.h"

using Core::McsManagerCoreChild;

McsManagerCoreChild::McsManagerCoreChild(IMcsManagerCore *core) : mCore(core)
{
}

Core::IMcsManagerCore *McsManagerCoreChild::getCore()
{
    return mCore;
}

Config::IConfigManager *McsManagerCoreChild::getConfigManager()
{
    if (mCore)
        return mCore->getConfigManager();

    return nullptr;
}

Backup::IBackupManager *McsManagerCoreChild::getBackupManager()
{
    if (mCore)
        return mCore->getBackupManager();

    return nullptr;
}

Server::IMcServerBuilder *McsManagerCoreChild::getServerBuilder()
{
    if (mCore)
        return mCore->getServerBuilder();

    return nullptr;
}

Server::IMcServer *McsManagerCoreChild::getCurrentServer()
{
    if (mCore)
        return mCore->getCurrentServer();

    return nullptr;
}
