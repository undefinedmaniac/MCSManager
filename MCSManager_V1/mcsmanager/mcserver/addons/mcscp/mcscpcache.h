#ifndef MCSCPCACHE_H
#define MCSCPCACHE_H

#include "mcscpperformancereport.h"
#include "mcscpplayerreport.h"

#include <QStringList>
#include <QHash>

class McscpCache
{
public:
    McscpCache();
    ~McscpCache();

    void setMaxPlayers(int maxPlayers);
    void setPlayerCount(int playerCount);
    void setPlayerList(const QStringList &playerList);
    void setMotd(const QString &motd);
    void appendToLog(const QString &data);
    void clearLog();
    void setPerformanceReport(const McscpPerformanceReport &performanceReport);

    void addPlayerReport(const McscpPlayerReport &playerReport);
    void removePlayerReport(const QString &name);
    void removeAllPlayerReports();

    int getMaxPlayers() const;
    int getPlayerCount() const;
    QStringList getPlayerList() const;
    QString getMotd() const;
    QStringList getLog() const;
    McscpPerformanceReport getPerformanceReport() const;
    McscpPlayerReport getPlayerReport(const QString &name) const;

private:
    int mMaxPlayers, mPlayerCount;
    QStringList mPlayerList;
    QString mMotd;
    QStringList mLog;
    McscpPerformanceReport mPerformanceReport;
    QHash<QString, McscpPlayerReport> mPlayerReports;
};

#endif // MCSCPCACHE_H
