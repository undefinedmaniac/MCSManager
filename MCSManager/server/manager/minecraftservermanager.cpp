#include "minecraftservermanager.h"

MinecraftServerManager::MinecraftServerManager()
{

}

void MinecraftServerManager::setConfig(const IServerManagerConfig *config)
{
    mConfig = config;
}

const IServerManagerConfig *MinecraftServerManager::config() const
{
    return mConfig;
}

void MinecraftServerManager::setServer(IMinecraftServer *server)
{
    mServer = server;

    if (server == nullptr)
        return;

    QObject *object = dynamic_cast<QObject *>(server);

    QObject::connect(object, SIGNAL(started()), this, SLOT(serverStarted()));
    QObject::connect(object, SIGNAL(stopped()), this, SLOT(serverStopped()));
}

IMinecraftServer *MinecraftServerManager::server()
{
    return mServer;
}

void MinecraftServerManager::startServer()
{
    if (mServer == nullptr)
        return;

    InternalState lastState = mState;
    mState = StartingServer;

    mServer->start();

    if (lastState == Idle)
        mServer->startAddons();
}

void MinecraftServerManager::stopServer(IServerManagerConfig::ShutdownBehavior behavior,
                                        const QString &altServer)
{
    if (mServer == nullptr)
        return;

    mState = StoppingServer;
    mServer->stop();

    shutdownAction(behavior, altServer);
}

void MinecraftServerManager::serverStarted()
{
    mState = ServerStarted;

    qDebug() << "Server [" << mServer->config()->name() << "]: Started!";
}

void MinecraftServerManager::serverStopped()
{
    InternalState lastState = mState;
    mState = ServerStopped;

    //Unexpected shutdown
    if (lastState != StoppingServer) {
        qDebug() << "Server [" << mServer->config()->name() << "]: Unexpected shutdown!";
        shutdownAction(mConfig->unexpectedShutdownBehavior(), mConfig->alternativeServerName());
    }

    qDebug() << "Server [" << mServer->config()->name() << "]: Stopped!";
}

void MinecraftServerManager::shutdownAction(IServerManagerConfig::ShutdownBehavior behavior,
                                            const QString &altServer)
{
    if (behavior != IServerManagerConfig::RestartServer) {
        mServer->stopAddons();
        mState = Idle;
    }

    switch (behavior) {
    case IServerManagerConfig::RestartServer:
        startServer();
        break;
    case IServerManagerConfig::StartAlternativeServer:
        getCore()->startServer(altServer); 
        break;
    default:
        break;
    }
}
