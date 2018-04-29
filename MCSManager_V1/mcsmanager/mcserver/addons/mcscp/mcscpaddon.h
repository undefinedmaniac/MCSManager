#ifndef MCSCPADDON_H
#define MCSCPADDON_H

#include "mcscpglobal.h"
#include "../mcserveraddonbase.h"
#include "mcscpconfigreader.h"
#include "mcscphandshake.h"
#include "interfaces/imcscpaddon.h"
#include "mcscpservertable.h"
#include "mcscpplayertable.h"
#include "interfaces/imcscpplayertable.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <QTcpSocket>
#include <QTimer>
#include <QRegularExpression>
#include <QHash>

namespace Mcscp { class McscpAddon; }

class Mcscp::McscpAddon : public IMcscpAddon, public Addon::McServerAddonBase
{
    Q_OBJECT
public:
    McscpAddon(Server::IMcServer *server, QObject *parent = nullptr);

    // IMcscpAddon interface
    bool isConnected() const;

    const IMcscpServerTable *getServerTable() const override;
    const IMcscpPlayerTable *getPlayerTable(const QString &uuid) const override;
    QStringList getPlayerUuids() const override;
    QStringList getPlayerList() const override;

    QString readEntireLog() override;
    QString readLogFromPos(int startingPos) override;

    void sendToConsole(const QString &command) override;
    void broadcast(const QString &message) override;
    void stopServer() override;

    // IMcServerAddon interface
    void preInit() override;
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void attemptConnection();

    void clientConnected();
    void clientDisconnected();
    void error(QAbstractSocket::SocketError error);
    void readyRead();

private:
    bool mIsRunning = false;

    QString mAddress;
    int mPort;

    QTcpSocket mSocket;
    Mcscp::McscpHandshake mHandshake;
    QTimer mConnectionTimer;

    Mcscp::McscpServerTable mServerTable;
    QHash<QString, Mcscp::McscpPlayerTable*> mPlayerTables;

    QString mServerLog;

    void removePlayerTable(const QString &uuid);

    void delayedConnection(int msecs);
    void disconnect();
    void handshakeComplete();

    void writeString(const QString &data);

    void serverTableUpdate(const QString &key, const QString &value);
    void playerTableUpdate(const QString &uuid, const QString &key, const QString &value);

    void playerEvent(const QString &type, const QString &uuid);
    void playerConnected(const QString &uuid);
    void playerDisconnected(const QString &uuid);

    void messageEvent(const QString &type, const QString &uuid, const QString &message);
    void deathMessage(const QString &uuid, const QString &message);
    void chatMessage(const QString &uuid, const QString &message);

    void logEvent(int oldSize);

    static const QRegularExpression SERVER_UPDATE_MATCHER,
                                    PLAYER_UPDATE_MATCHER,
                                    PLAYER_EVENT_MATCHER,
                                    MESSAGE_EVENT_MATCHER,
                                    SERVER_LOG_MATCHER;
};

#endif // MCSCPADDON_H
