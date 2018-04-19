#include "mcscpaddon.h"

McscpAddon::McscpAddon(IMcServer *server, QObject *parent) :
    QObject(parent), McServerAddonBase(QStringLiteral("mcscp"), server)
{
    connect(&mSocket, SIGNAL(connected()), SLOT(connected()));
    connect(&mSocket, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(error(QAbstractSocket::SocketError)));
    connect(&mSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            SLOT(stateChanged(QAbstractSocket::SocketState)));

    connect(&mSocket, SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten(qint64)));
    connect(&mSocket, SIGNAL(readyRead()), SLOT(readyRead()));

    connect(&mConnectionTimer, SIGNAL(timeout()), SLOT(attemptConnection()));

    mConnectionTimer.setSingleShot(true);
}

void McscpAddon::preInit()
{
    McscpConfigReader reader(getServer()->getConfig()->getAddonConfig(getName()));
    mAddress = reader.address();
    mPort = reader.port();
}

void McscpAddon::init()
{
}

void McscpAddon::start()
{
    mIsRunning = true;
    delayedConnection(5000);
}

void McscpAddon::stop()
{
    mIsRunning = false;
    mSocket.disconnectFromHost();
}

bool McscpAddon::isRunning() const
{
    return mIsRunning;
}

void McscpAddon::attemptConnection()
{
    if (isRunning())
        mSocket.connectToHost(mAddress, mPort);
}

void McscpAddon::connected()
{
    qDebug() << "MCSCP Connected!";
    mHandshake.reset(new McscpHandshake());
}

void McscpAddon::disconnected()
{
    qDebug() << "MCSCP Disconnected!";
    delayedConnection(5000);
}

void McscpAddon::error(QAbstractSocket::SocketError error)
{
    qDebug() << "MCSCP Error:" << mSocket.errorString();

    if (error == QAbstractSocket::ConnectionRefusedError)
        delayedConnection(5000);
}

void McscpAddon::stateChanged(QAbstractSocket::SocketState state)
{

}

void McscpAddon::bytesWritten(qint64 bytes)
{

}

void McscpAddon::readyRead()
{
    if (!mHandshake.isNull() && !mHandshake->isComplete()) {
        mHandshake->processData(QString::fromUtf8(mSocket.readAll()));
        writeString(mHandshake->getNextMessage());
    }
}

void McscpAddon::delayedConnection(int msecs)
{
    mConnectionTimer.start(msecs);
}

void McscpAddon::writeString(const QString &data)
{
    mSocket.write(data.toUtf8());
}
