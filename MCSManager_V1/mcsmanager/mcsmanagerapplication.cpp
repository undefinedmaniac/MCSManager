#include "mcsmanagerapplication.h"

using Application::McsManagerApplication;

McsManagerApplication::McsManagerApplication(QObject *parent) : QObject(parent), mCore(),
    mConfigManager(&mCore), mBackupManager(&mCore), mServerBuilder(&mCore)
{
    mCore.setComponents(&mConfigManager, &mBackupManager, &mServerBuilder);

    connect(&mCommandLine, SIGNAL(exitApplication()), SLOT(exitApplication()));
}

void McsManagerApplication::start()
{
    mCommandLine.start(&mCore);

    mCore.loadConfigs(joinPaths(QCoreApplication::applicationDirPath(), QStringLiteral("config")));
    mCore.startDefaultServer();
}

void McsManagerApplication::exitApplication()
{
    if (Server::IMcServer *server = mCore.getCurrentServer()) {
        if (server->isRunning()) {
            server->stop();
            QEventLoop loop;
            connect(server, SIGNAL(stopped(bool)), &loop, SLOT(quit()));
            loop.exec();
        }
    }

    QCoreApplication::quit();
}
