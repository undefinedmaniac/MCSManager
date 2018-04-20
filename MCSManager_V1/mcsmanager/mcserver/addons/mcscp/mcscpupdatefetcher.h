#ifndef MCSCPUPDATEFETCHER_H
#define MCSCPUPDATEFETCHER_H

#include "mcscpcache.h"

#include <QString>
#include <QRegularExpression>

class McscpUpdateFetcher
{
public:
    McscpUpdateFetcher();

    bool hasNextMessage() const;

    QString getNextMessage();

    void responseReceived(const QString &data);

    McscpCache getData() const;

    void reset();

private:
    enum State {
        MaxPlayers, PlayerCount, PlayerList,
        PerformanceReport, Motd, Log, Finished
    };

    State mState = MaxPlayers;
    McscpCache mCache;

    static const QRegularExpression PLAYER_LIST_MATCHER;
};

#endif // MCSCPUPDATEFETCHER_H
