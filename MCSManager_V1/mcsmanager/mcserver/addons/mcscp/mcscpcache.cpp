#include "mcscpcache.h"

McscpCache::McscpCache()
{ 
}

void McscpCache::setMaxPlayers(int maxPlayers)
{
    mMaxPlayers = maxPlayers;
}

void McscpCache::setPlayerCount(int playerCount)
{
    mPlayerCount = playerCount;
}

void McscpCache::setPlayerList(const QStringList &playerList)
{
    mPlayerList = playerList;
}

void McscpCache::setMotd(const QString &motd)
{
    mMotd = motd;
}

void McscpCache::appendToLog(const QString &data)
{
    mLog.append(data);
}

void McscpCache::clearLog()
{
    mLog.clear();
}

void McscpCache::setPerformanceReport(const McscpPerformanceReport &performanceReport)
{
    mPerformanceReport = performanceReport;
}

void McscpCache::addPlayerReport(const McscpPlayerReport &playerReport)
{
    mPlayerReports.insert(playerReport.getName(), playerReport);
}

void McscpCache::removePlayerReport(const QString &name)
{
    mPlayerReports.remove(name);
}

void McscpCache::removeAllPlayerReports()
{
    mPlayerReports.clear();
}

int McscpCache::getMaxPlayers() const
{
    return mMaxPlayers;
}

int McscpCache::getPlayerCount() const
{
    return mPlayerCount;
}

QStringList McscpCache::getPlayerList() const
{
    return mPlayerList;
}

QString McscpCache::getMotd() const
{
    return mMotd;
}

QStringList McscpCache::getLog() const
{
    return mLog;
}

McscpPerformanceReport McscpCache::getPerformanceReport() const
{
    return mPerformanceReport;
}

McscpPlayerReport McscpCache::getPlayerReport(const QString &name) const
{
    return mPlayerReports.value(name);
}
