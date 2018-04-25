#include "sleeperaddon.h"

SleeperAddon::SleeperAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(SleeperConfigReader::getAddonName(), server)
{
    mTimer.setTimerType(Qt::VeryCoarseTimer);
    mTimer.setSingleShot(true);
    connect(&mTimer, SIGNAL(timeout()), SLOT(sleepTimerExpired()));
}

void SleeperAddon::preInit()
{
    SleeperConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));

    mPeriod = reader.period() * 60000; //Convert minutes to milliseconds
    mShutdownBehavior = reader.shutdownBehavior();
    mAltServer = reader.alternativeServer();

    if (mPeriod > 0)
        mConfigIsValid = true;
}

void SleeperAddon::init()
{
    if (mConfigIsValid) {
        IMcscpAddon *mcscpAddon = dynamic_cast<IMcscpAddon*>(getServer()->getAddon(QStringLiteral("mcscp")));
        if (mcscpAddon) {
            mTable = mcscpAddon->getServerTable();

            if (mTable) {
                mTimer.setInterval(mPeriod);
                connect(mcscpAddon, SIGNAL(connected()), SLOT(mcscpConnected()));
                connect(mcscpAddon, SIGNAL(disconnected()), SLOT(mcscpDisconnected()));
                connect(mTable, SIGNAL(KeyUpdate(IMcscpServerTable::Key)), SLOT(playerCountChanged(IMcscpServerTable::Key)));
            }
        }
    }
}

void SleeperAddon::start()
{
    if (mConfigIsValid && mTable)
        mIsRunning = true;
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
    if (key == IMcscpServerTable::PlayerCount)
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

void SleeperAddon::mcscpConnected()
{
    checkPlayerCount();
}

void SleeperAddon::mcscpDisconnected()
{
    mTimer.stop();
}

void SleeperAddon::checkPlayerCount()
{
    if (isRunning()) {
        int playerCount = mTable->getPlayerCount();
        if (playerCount == 0)
            mTimer.start();
        else
            mTimer.stop();
    }
}
