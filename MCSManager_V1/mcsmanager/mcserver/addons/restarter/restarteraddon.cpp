#include "restarteraddon.h"

RestarterAddon::RestarterAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(RestarterConfigReader::getAddonName(), server)
{   
    mTimer.setTimerType(Qt::VeryCoarseTimer);
    mTimer.setSingleShot(true);
    mTimer.setInterval(1000);
    connect(&mTimer, SIGNAL(timeout()), SLOT(timeout()));
}

void RestarterAddon::preInit()
{
    RestarterConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mPeriod = reader.period() * 60; //Convert minutes to seconds

    if (mPeriod >= 300)
        mConfigIsValid = true;
}

void RestarterAddon::init()
{
    if (mConfigIsValid) {
        IMcscpAddon *addon = dynamic_cast<IMcscpAddon*>(getServer()->getAddon(QStringLiteral("mcscp")));
        if (addon) {
            mMcscpAddonLocated = true;
            mMcscpAddon = addon;
        }
    }
}

void RestarterAddon::start()
{
    //300 seconds == 5 minutes
    if (mConfigIsValid) {
        if (mMcscpAddonLocated) {
            mIsRunning = true;
            mSeconds = mPeriod;
            mTimer.start();
        } else {
            //Tell the user that the MCSCP addon is required
        }
    } else {
        //Tell user that period must be >= 5 minutes;
    }
}

void RestarterAddon::stop()
{
    mIsRunning = false;
    mTimer.stop();
}

bool RestarterAddon::isRunning() const
{
    return mIsRunning;
}

//Fired every second while the server is running
void RestarterAddon::timeout()
{
    if (mSeconds <= 0) {
        mTimer.stop();
        getServer()->restart();
    } else if ((mSeconds == 300 || mSeconds == 180 || mSeconds == 60 ||
                mSeconds == 30 || mSeconds == 10 || mSeconds <= 5)) {
        mMcscpAddon->broadcast(getBroadcastMessage());
    }

    mSeconds--;
}

QString RestarterAddon::getBroadcastMessage()
{
    QString message = QStringLiteral("&d[Server Restarter] The server will restart in ");

    if (mSeconds > 60) {
        message += QString::number(mSeconds / 60);
        message += QStringLiteral(" minutes!");
    } else if (mSeconds == 60){
        message += QStringLiteral("1 minute!");
    } else if (mSeconds == 1) {
        message += QStringLiteral("1 second!");
    } else {
        message += QString::number(mSeconds);
        message += QStringLiteral(" seconds!");
    }

    return message;
}
