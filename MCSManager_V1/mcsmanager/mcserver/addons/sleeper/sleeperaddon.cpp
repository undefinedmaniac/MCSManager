#include "sleeperaddon.h"

SleeperAddon::SleeperAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(QStringLiteral("sleeper"), server)
{
    mTimer.setTimerType(Qt::VeryCoarseTimer);
    mTimer.setSingleShot(true);
    connect(&mTimer, SIGNAL(timeout()), SLOT(sleepTimerExpired()));
}

void SleeperAddon::preInit()
{
    SleeperConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));

    mPeriod = reader.period();
    mShutdownBehavior = reader.shutdownBehavior();
    mAltServer = reader.alternativeServer();
}

void SleeperAddon::init()
{
    IMcscpAddon *mcscpAddon = dynamic_cast<IMcscpAddon*>(getServer()->getAddon(QStringLiteral("mcscp")));
    if (mcscpAddon != nullptr) {
        mTable = mcscpAddon->getServerTable();
        connect(mTable, SIGNAL(KeyUpdate(IMcscpServerTable::Key)), SLOT(playerCountChanged(IMcscpServerTable::Key)));
    }
}

void SleeperAddon::start()
{
    if (mPeriod > 0) {
        mTimer.setInterval(mPeriod * 60000);
        mIsRunning = true;
        checkPlayerCount();
    }
}

void SleeperAddon::stop()
{
    mIsRunning = false;
    mTimer.stop();
}

bool SleeperAddon::isRunning() const
{
    return mIsRunning;
}

void SleeperAddon::playerCountChanged(IMcscpServerTable::Key key)
{
    if (mIsRunning && key == IMcscpServerTable::PlayerCount)
        checkPlayerCount();
}

void SleeperAddon::sleepTimerExpired()
{
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

void SleeperAddon::checkPlayerCount()
{
    int playerCount = mTable->getPlayerCount();
    if (playerCount == 0)
        mTimer.start();
    else
        mTimer.stop();
}
