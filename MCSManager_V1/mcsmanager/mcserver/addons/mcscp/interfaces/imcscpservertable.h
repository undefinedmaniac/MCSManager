#ifndef IMCSCPSERVERTABLE_H
#define IMCSCPSERVERTABLE_H

class QString;

#include <QObject>

namespace Mcscp { class IMcscpServerTable; }

class Mcscp::IMcscpServerTable : public QObject
{
    Q_OBJECT
public:
    IMcscpServerTable(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IMcscpServerTable() {}

    enum Key {
        MaxPlayers, PlayerCount, Motd, Tps, MaxRam,
        TotalRam, UsedRam
    };

    virtual int getMaxPlayers() const = 0;
    virtual int getPlayerCount() const = 0;
    virtual QString getMotd() const = 0;
    virtual float getTps() const = 0;
    virtual float getMaxRam() const = 0;
    virtual float getTotalRam() const = 0;
    virtual float getUsedRam() const = 0;

signals:
    void KeyUpdate(IMcscpServerTable::Key key);
};

#endif // IMCSCPSERVERTABLE_H
