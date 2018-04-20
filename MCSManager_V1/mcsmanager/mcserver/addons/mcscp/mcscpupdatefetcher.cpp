#include "mcscpupdatefetcher.h"

const QRegularExpression McscpUpdateFetcher::PLAYER_LIST_MATCHER(QStringLiteral("(?<!^)\[(.*?)]"));

McscpUpdateFetcher::McscpUpdateFetcher()
{
}

bool McscpUpdateFetcher::hasNextMessage() const
{
    return mState != Finished;
}

QString McscpUpdateFetcher::getNextMessage()
{
    switch (mState) {
    case MaxPlayers:
        return QStringLiteral("[REQUEST]:[TYPE:MAXPLAYERS]");
    case PlayerCount:
        return QStringLiteral("[REQUEST]:[TYPE:PLAYERCOUNT]");
    case PlayerList:
        return QStringLiteral("[REQUEST]:[TYPE:PLAYERLIST]");
    case PlayerReports: {

    }
    }
}

void McscpUpdateFetcher::responseReceived(const QString &data)
{
    switch (mState) {
    case MaxPlayers: {
        mState = PlayerCount;
        mCache.setMaxPlayers(data.toInt());
    }
    case PlayerCount: {
        mState = PlayerList;
        mCache.setPlayerCount(data.toInt());
    }
    case PlayerList: {
        mState = PlayerReports;
        QRegularExpressionMatchIterator iterator = PLAYER_LIST_MATCHER.globalMatch(data);
        QStringList playerList;

        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            playerList.append(match.captured(1));
        }

        mCache.setPlayerList(playerList);
    }
    }
}

McscpCache McscpUpdateFetcher::getData() const
{
    return mCache;
}

void McscpUpdateFetcher::reset()
{
    mCache.clearLog();
    mCache.removeAllPlayerReports();
}
