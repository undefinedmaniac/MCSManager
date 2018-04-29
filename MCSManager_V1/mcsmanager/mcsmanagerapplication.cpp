#include "mcsmanagerapplication.h"

using Application::McsManagerApplication;

McsManagerApplication::McsManagerApplication() : mCore(), mConfigManager(&mCore),
    mBackupManager(&mCore), mServerBuilder(&mCore)
{
    mCore.setComponents(&mConfigManager, &mBackupManager, &mServerBuilder);
}

void McsManagerApplication::start()
{
    mCommandLine.start(&mCore);

    mCore.loadConfigs(joinPaths(QCoreApplication::applicationDirPath(), QStringLiteral("config")));
    mCore.startDefaultServer();
}
