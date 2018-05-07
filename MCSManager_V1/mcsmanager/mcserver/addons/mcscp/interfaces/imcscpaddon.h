#ifndef IMCSCPADDON_H
#define IMCSCPADDON_H

class QString;
class QStringList;

#include <QObject>

namespace Mcscp
{
    class IMcscpAddon;
    class IMcscpServerTable;
    class IMcscpPlayerTable;
}

class Mcscp::IMcscpAddon : public QObject
{
    Q_OBJECT
public:
    IMcscpAddon(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IMcscpAddon() {}

    virtual bool isConnected() const = 0;

    virtual const Mcscp::IMcscpServerTable *getServerTable() const = 0;
    virtual const Mcscp::IMcscpPlayerTable *getPlayerTable(const QString &uuid) const = 0;
    virtual QStringList getPlayerUuids() const = 0;
    virtual QStringList getPlayerList() const = 0;

    virtual QString readEntireLog() = 0;
    virtual QString readLogFromPos(int startingPos) = 0;

    virtual void sendToConsole(const QString &command) = 0;
    virtual void broadcast(const QString &message) = 0;
    virtual void stopServer() = 0;

signals:
    void connected();
    void disconnected();
    void playerJoined(QString uuid);
    void playerLeft(QString uuid);
    void playerDied(QString uuid, QString deathMessage);
    void chatEvent(QString uuid, QString message);
    void newLogData(int startingPos);
};

#endif // IMCSCPADDON_H
