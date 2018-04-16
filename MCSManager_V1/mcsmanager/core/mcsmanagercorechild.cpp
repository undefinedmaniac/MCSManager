#include "mcsmanagercorechild.h"

McsManagerCoreChild::McsManagerCoreChild(IMcsManagerCore *core) : mCore(core)
{
}

IMcsManagerCore *McsManagerCoreChild::getCore()
{
    return mCore;
}

IConfigManager *McsManagerCoreChild::getConfigManager()
{
    if (mCore)
        return mCore->getConfigManager();

    return nullptr;
}

IBackupManager *McsManagerCoreChild::getBackupManager()
{
    if (mCore)
        return mCore->getBackupManager();

    return nullptr;
}

IMcServerBuilder *McsManagerCoreChild::getServerBuilder()
{
    if (mCore)
        return mCore->getServerBuilder();

    return nullptr;
}

IMcServer *McsManagerCoreChild::getCurrentServer()
{
    if (mCore)
        return mCore->getCurrentServer();

    return nullptr;
}
