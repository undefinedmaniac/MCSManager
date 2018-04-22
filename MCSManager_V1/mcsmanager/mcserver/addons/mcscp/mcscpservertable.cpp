#include "mcscpservertable.h"

McscpServerTable::McscpServerTable(QObject *parent) : IMcscpServerTable(parent)
{
}

void McscpServerTable::setMaxPlayers(int maxPlayers)
{
    mMaxPlayers = maxPlayers;
    emit KeyUpdate(Key::MaxPlayers);
}

void McscpServerTable::setPlayerCount(int playerCount)
{
    mPlayerCount = playerCount;
    emit KeyUpdate(Key::PlayerCount);
}

void McscpServerTable::setMotd(const QString &motd)
{
    mMotd = motd;
    emit KeyUpdate(Key::Motd);
}

void McscpServerTable::setTps(float tps)
{
    mTps = tps;
    emit KeyUpdate(Key::Tps);
}

void McscpServerTable::setMaxRam(float maxRam)
{
    mMaxRam = maxRam;
    emit KeyUpdate(Key::MaxRam);
}

void McscpServerTable::setTotalRam(float totalRam)
{
    mTotalRam = totalRam;
    emit KeyUpdate(Key::TotalRam);
}

void McscpServerTable::setUsedRam(float usedRam)
{
    mUsedRam = usedRam;
    emit KeyUpdate(Key::UsedRam);
}

int McscpServerTable::getMaxPlayers() const
{
    return mMaxPlayers;
}

int McscpServerTable::getPlayerCount() const
{
    return mPlayerCount;
}

QString McscpServerTable::getMotd() const
{
    return mMotd;
}

float McscpServerTable::getTps() const
{
    return mTps;
}

float McscpServerTable::maxRam() const
{
    return mMaxRam;
}

float McscpServerTable::totalRam() const
{
    return mTotalRam;
}

float McscpServerTable::usedRam() const
{
    return mUsedRam;
}
