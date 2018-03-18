#include "minecraftservermanager.h"

MinecraftServerManager::MinecraftServerManager()
{

}

const IServerManagerConfig *MinecraftServerManager::config() const
{
    if (mServer == nullptr)
        return nullptr;

    return mServer->config();
}

void MinecraftServerManager::setServer(IMinecraftServer *server)
{
    mState = Idle;
    mServer = server;

    if (server == nullptr)
        return;

    server->setServerManager(this);

    QObject *object = dynamic_cast<QObject *>(server);

    if (object != nullptr) {
        QObject::connect(object, SIGNAL(started()), this, SLOT(serverStarted()));
        QObject::connect(object, SIGNAL(stopped()), this, SLOT(serverStopped()));
    }
}

IMinecraftServer *MinecraftServerManager::server()
{
    return mServer;
}

void MinecraftServerManager::startServer()
{
    if (mServer == nullptr)
        return;

    mState = StartingServer;

    mServer->start();
}

void MinecraftServerManager::stopServer(IServerManagerConfig::ShutdownBehavior behavior,
                                        const QString &altServer)
{
    if (mServer == nullptr || !mServer->isRunning())
        return;

    mState = StoppingServer;
    mServer->stop();

    shutdownAction(behavior, altServer);
}

//Beep boop. The server is up!
void MinecraftServerManager::serverStarted()
{
    mState = ServerStarted;
}

//Goodbye players, the server is down
void MinecraftServerManager::serverStopped()
{
    InternalState lastState = mState;
    mState = ServerStopped;

    //Unexpected shutdown - someone planted a giant oak tree again!
    if (lastState != StoppingServer) {
        qDebug() << "Unexpected server shutdown!";

        const IServerManagerConfig *serverConfig = config();

        if (serverConfig != nullptr)
            shutdownAction(serverConfig->unexpectedShutdownBehavior(), serverConfig->alternativeServerName());
    }
}

void MinecraftServerManager::shutdownAction(IServerManagerConfig::ShutdownBehavior behavior,
                                            const QString &altServer)
{
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
