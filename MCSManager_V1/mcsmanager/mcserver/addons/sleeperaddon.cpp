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

    SleeperConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mPeriod = reader.period();
    mShutdownBehavior = reader.shutdownBehavior();
    mAltServer = reader.alternativeServer();
}

void SleeperAddon::init()
{
    qDebug() << "Init!";

    if (mPeriod > 0) {
        mPeriod *= 1000;

        mTimer.setInterval(mPeriod);
        mTimer.setTimerType(Qt::VeryCoarseTimer);

        connect(&mTimer, &QTimer::timeout, this, &SleeperAddon::timeout);
    }
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

    switch (mShutdownBehavior) {
    case ConfigGlobal::Restart:
        getServer()->restart();
        break;
    case ConfigGlobal::StartAltServer:
        if (IMcsManagerCore *core = getCore())
            core->startServer(mAltServer);
        break;
    default:
        getServer()->stop();
        break;
    }
}
