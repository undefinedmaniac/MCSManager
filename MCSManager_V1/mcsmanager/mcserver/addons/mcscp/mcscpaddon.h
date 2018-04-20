#ifndef MCSCPADDON_H
#define MCSCPADDON_H

#include "../mcserveraddonbase.h"
#include "mcscpconfigreader.h"
#include "mcscphandshake.h"
#include "mcscpcache.h"

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include <QTcpSocket>
#include <QTimer>

class McscpAddon : public QObject, public McServerAddonBase
{
    Q_OBJECT
public:
    McscpAddon(IMcServer *server, QObject *parent = nullptr);

    void update();

    // IMcServerAddon interface
    void preInit() override;
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void attemptConnection();

    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError error);
    void stateChanged(QAbstractSocket::SocketState state);

    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    bool mIsRunning = false;
    QString mAddress;
    int mPort;

    QTcpSocket mSocket;
    McscpHandshake mHandshake;

    QTimer mConnectionTimer;

    McscpCache mCache;

    void delayedConnection(int msecs);
    void writeString(const QString &data);
    void disconnect();
};

#endif // MCSCPADDON_H
