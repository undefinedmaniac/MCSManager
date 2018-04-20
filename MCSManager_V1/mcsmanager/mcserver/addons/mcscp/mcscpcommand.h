#ifndef MCSCPCOMMAND_H
#define MCSCPCOMMAND_H

#include <QString>
#include <QStringList>

class McscpCommand
{
public:
    enum Type {
        Console, Chat, Broadcast, GetMaxPlayers, GetPlayerCount, GetPlayerList,
        GetPlayerReport, GetTps, GetPerformanceReport, GetMaxRam, GetTotalRam,
        GetFreeRam, GetUsedRam, GetMotd, GetLog, Stop, SetFlag, Ping
    };

    McscpCommand(Type commandType);

    void addData(const QString &data);

    Type getCommandType() const;
    QStringList getData() const;


private:
    QStringList mData;

};

#endif // MCSCPCOMMAND_H
