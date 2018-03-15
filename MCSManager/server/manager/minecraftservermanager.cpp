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
}

IMinecraftServer *MinecraftServerManager::server()
{
    return mServer;
}

void MinecraftServerManager::startServer()
{
    mServer->start();
}

void MinecraftServerManager::stopServer(IServerManagerConfig::ShutdownBehavior behavior)
{
    mServer->stop();
}

void MinecraftServerManager::serverStoped()
{

}
