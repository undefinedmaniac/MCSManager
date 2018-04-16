#include "sleeperaddon.h"

SleeperAddon::SleeperAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(QStringLiteral("server_sleeper"), server)
{
}

SleeperAddon::~SleeperAddon()
{
    qDebug() << "Destroyed!";
}

void SleeperAddon::preInit()
{
    qDebug() << "Pre-Init!";

    //Get the config file
    mConfig = getServer()->getConfig()->getAddonConfig(getName());
    mPeriod = mConfig->readDouble(QStringLiteral("period"));
}

void SleeperAddon::init()
{
    qDebug() << "Init!";

    if (mPeriod != -1)
        mPeriod *= 1000;

    mTimer.setInterval(mPeriod);
    mTimer.setTimerType(Qt::VeryCoarseTimer);

    connect(&mTimer, &QTimer::timeout, this, &SleeperAddon::timeout);
}

void SleeperAddon::start()
{
    qDebug() << "Started!";
    mIsRunning = true;
    mTimer.start();
}

void SleeperAddon::stop()
{
    qDebug() << "Stopped!";
    mIsRunning = false;
    mTimer.stop();
}

bool SleeperAddon::isRunning() const
{
    return mIsRunning;
}

void SleeperAddon::timeout()
{
    qDebug() << "Timed out!";
    getServer()->stop();
}
