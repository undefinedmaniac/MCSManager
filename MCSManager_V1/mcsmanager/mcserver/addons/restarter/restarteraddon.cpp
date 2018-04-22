#include "restarteraddon.h"

RestarterAddon::RestarterAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(QStringLiteral("auto_restart"), server)
{
}

RestarterAddon::~RestarterAddon()
{
    qDebug() << "Destroyed!";
}

void RestarterAddon::preInit()
{
    qDebug() << "Pre-Init!";

    RestarterConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mPeriod = reader.period();
    mShutdownBehavior = reader.shutdownBehavior();
    mAltServer = reader.alternativeServer();
}

void RestarterAddon::init()
{
    qDebug() << "Init!";

    if (mPeriod > 0) {
        mPeriod *= 1000;

        mTimer.setInterval(mPeriod);
        mTimer.setTimerType(Qt::VeryCoarseTimer);

        connect(&mTimer, &QTimer::timeout, this, &RestarterAddon::timeout);
    }
}

void RestarterAddon::start()
{
    qDebug() << "Started!";
    mIsRunning = true;
    mTimer.start();
}

void RestarterAddon::stop()
{
    qDebug() << "Stopped!";
    mIsRunning = false;
    mTimer.stop();
}

bool RestarterAddon::isRunning() const
{
    return mIsRunning;
}

void RestarterAddon::timeout()
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
