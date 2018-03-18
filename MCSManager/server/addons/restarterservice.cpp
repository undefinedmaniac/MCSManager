#include "restarterservice.h"

RestarterService::RestarterService(const QString &name, IMinecraftServer *server) :
    MinecraftServerAddonBase(name, server)
{
    connect(&mTimer, &QTimer::timeout, this, &RestarterService::timeout);
}

void RestarterService::start()
{
    qDebug() << "Restarter service started!";

    const IRestarterAddonConfig *config = server()->config();

    int timerMsecs = config->restarterPeriod() * 1000;

    mTimer.start(timerMsecs);
}

void RestarterService::stop()
{
    mTimer.stop();
}

bool RestarterService::isRunning()
{
    return mTimer.isActive();
}

const IRestarterAddonConfig *RestarterService::config() const
{
    return server()->config();
}

int RestarterService::timeUntilRestart() const
{
    return (mTimer.remainingTime() * .001);
}

void RestarterService::timeout()
{
    IMinecraftServerManager *manager = server()->serverManager();

    if (manager != nullptr)
        manager->stopServer(IServerManagerConfig::RestartServer);
}
