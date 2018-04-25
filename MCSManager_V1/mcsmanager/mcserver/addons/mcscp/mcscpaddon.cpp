#include "mcscpaddon.h"

const QRegularExpression McscpAddon::SERVER_UPDATE_MATCHER(QStringLiteral("(?i)\\[UPDATE]:\\[KEY:(.*)]:\\[VALUE:(.*)]")),
                         McscpAddon::PLAYER_UPDATE_MATCHER(QStringLiteral("(?i)\\[UPDATE]:\\[KEY:PLAYER:(.*)]:\\[UUID:(.*)]:\\[VALUE:(.*)]")),
                         McscpAddon::PLAYER_EVENT_MATCHER(QStringLiteral("(?i)\\[EVENT]:\\[TYPE:(.*)]:\\[UUID:(.*)]")),
                         McscpAddon::MESSAGE_EVENT_MATCHER(QStringLiteral("(?i)\\[EVENT]:\\[TYPE:(.*)]:\\[UUID:(.*)]:\\[MESSAGE:(.*)]")),
                         McscpAddon::SERVER_LOG_MATCHER(QStringLiteral("(?i)\\[LOG]:\\[DATA:(.*)]"));

McscpAddon::McscpAddon(IMcServer *server, QObject *parent) :
    IMcscpAddon(parent), McServerAddonBase(McscpConfigReader::getAddonName(), server)
{
    connect(&mSocket, SIGNAL(connected()), SLOT(clientConnected()));
    connect(&mSocket, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    connect(&mSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(error(QAbstractSocket::SocketError)));
    connect(&mSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            SLOT(stateChanged(QAbstractSocket::SocketState)));

    connect(&mSocket, SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten(qint64)));
    connect(&mSocket, SIGNAL(readyRead()), SLOT(readyRead()));

    connect(&mConnectionTimer, SIGNAL(timeout()), SLOT(attemptConnection()));

    mConnectionTimer.setSingleShot(true);
}

bool McscpAddon::isConnected() const
{
    return mSocket.isOpen();
}

const IMcscpServerTable *McscpAddon::getServerTable() const
{
    return &mServerTable;
}

const IMcscpPlayerTable *McscpAddon::getPlayerTable(const QString &uuid) const
{
    return mPlayerTables.value(uuid.toUpper(), nullptr);
}

QStringList McscpAddon::getPlayerUuids() const
{
    return mPlayerTables.keys();
}

QString McscpAddon::readEntireLog()
{
    return mServerLog;
}

QString McscpAddon::readLogFromPos(int startingPos)
{
    return mServerLog.mid(startingPos);
}

void McscpAddon::sendToConsole(const QString &command)
{
    writeString(QStringLiteral("[CMD]:[CONTENT:") + command + QStringLiteral("]"));
}

void McscpAddon::broadcast(const QString &message)
{
    writeString(QStringLiteral("[BROADCAST]:[CONTENT:") + message + QStringLiteral("]"));
}

void McscpAddon::stopServer()
{
    writeString(QStringLiteral("[STOP]"));
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
    mConnectionTimer.stop();

    if (isRunning())
        mSocket.connectToHost(mAddress, mPort);
}

void McscpAddon::clientConnected()
{
    qDebug() << "MCSCP Connected!";
    mHandshake.reset();
}

//Oh no, we dropped the connection
//"That hasen't happened for the longest time" - Billy Joel
void McscpAddon::clientDisconnected()
{
    qDebug() << "MCSCP Disconnected!";
    foreach (const QString &uuid, mPlayerTables.keys())
        playerDisconnected(uuid);
    mServerLog.clear();
    delayedConnection(5000);
}

void McscpAddon::error(QAbstractSocket::SocketError error)
{
    if (error == QAbstractSocket::ConnectionRefusedError)
        delayedConnection(5000);
    else
        qDebug() << "MCSCP Error:" << mSocket.errorString();
}

void McscpAddon::readyRead()
{
    QStringList lines;

    while (mSocket.canReadLine()) {
        const QString line = QString::fromUtf8(mSocket.readLine()).trimmed();
        lines.append(line);
    }

    foreach (const QString &data, lines) {
        if (!mHandshake.isComplete()) {
            if (mHandshake.processData(data)) {
                writeString(mHandshake.getNextMessage());
                if (mHandshake.isComplete())
                    handshakeComplete();
            } else {
                disconnect();
            }
        } else {
            //Here is where new table data will come in
            QRegularExpressionMatch match;

            match = PLAYER_UPDATE_MATCHER.match(data);
            if (match.hasMatch()) {
                const QString uuid = match.captured(2);
                const QString key = match.captured(1);
                const QString value = match.captured(3);
                playerTableUpdate(uuid, key, value);
                continue;
            }

            match = SERVER_UPDATE_MATCHER.match(data);
            if (match.hasMatch()) {
                const QString key = match.captured(1);
                const QString value = match.captured(2);
                serverTableUpdate(key, value);
                continue;
            }

            match = MESSAGE_EVENT_MATCHER.match(data);

            if (match.hasMatch()) {
                const QString type = match.captured(1);
                const QString uuid = match.captured(2);
                const QString message = match.captured(3);
                messageEvent(type, uuid, message);
                continue;
            }

            match = PLAYER_EVENT_MATCHER.match(data);
            if (match.hasMatch()) {
                const QString type = match.captured(1);
                const QString uuid = match.captured(2);
                playerEvent(type, uuid);
                continue;
            }

            match = SERVER_LOG_MATCHER.match(data);
            if (match.hasMatch()) {
                const QString logData = match.captured(1);
                int oldSize = mServerLog.size();
                mServerLog.append(logData);
                logEvent(oldSize);
            }
        }
    }
}

void McscpAddon::removePlayerTable(const QString &uuid)
{
    McscpPlayerTable *table = mPlayerTables.value(uuid, nullptr);

    if (table != nullptr) {
        mPlayerTables.remove(uuid);
        table->alertPlayerDisconnected();
        table->deleteLater();
    }
}

void McscpAddon::delayedConnection(int msecs)
{
    mConnectionTimer.start(msecs);
}

void McscpAddon::disconnect()
{
    mSocket.disconnectFromHost();
}

void McscpAddon::handshakeComplete()
{
    writeString(QStringLiteral("[SETFLAG]:[NAME:REPORTPLAYERLEAVE]:[VALUE:TRUE]"));
    writeString(QStringLiteral("[SETFLAG]:[NAME:REPORTCHAT]:[VALUE:TRUE]"));
    writeString(QStringLiteral("[SETFLAG]:[NAME:REPORTPLAYERDEATH]:[VALUE:TRUE]"));
    writeString(QStringLiteral("[SETFLAG]:[NAME:SENDSERVERLOG]:[VALUE:TRUE]"));
    emit connected();
}

void McscpAddon::writeString(const QString &data)
{
    mSocket.write((data + "\r\n").toUtf8());
}

void McscpAddon::serverTableUpdate(const QString &key, const QString &value)
{
    const QString upperKey = key.toUpper();

    if (upperKey == QStringLiteral("MAXPLAYERS"))
        mServerTable.setMaxPlayers(value.toInt());
    else if (upperKey == QStringLiteral("PLAYERCOUNT"))
        mServerTable.setPlayerCount(value.toInt());
    else if (upperKey == QStringLiteral("MOTD"))
        mServerTable.setMotd(value);
    else if (upperKey == QStringLiteral("TPS"))
        mServerTable.setTps(value.toFloat());
    else if (upperKey == QStringLiteral("MAXRAM"))
        mServerTable.setMaxRam(value.toFloat());
    else if (upperKey == QStringLiteral("TOTALRAM"))
        mServerTable.setTotalRam(value.toFloat());
    else if (upperKey == QStringLiteral("USEDRAM"))
        mServerTable.setUsedRam(value.toFloat());
}

void McscpAddon::playerTableUpdate(const QString &uuid, const QString &key, const QString &value)
{
    const QString upperUuid = uuid.toUpper();
    const QString upperKey = key.toUpper();

    McscpPlayerTable *table = mPlayerTables.value(upperUuid, nullptr);

    if (table == nullptr) {
        table = new McscpPlayerTable(this);
        mPlayerTables.insert(upperUuid, table);
        playerConnected(uuid);
    }

    if (upperKey == QStringLiteral("NAME"))
        table->setName(value);
    else if (upperKey == QStringLiteral("DISPLAYNAME"))
        table->setDisplayName(value);
    else if (upperKey == QStringLiteral("IP"))
        table->setIpAddress(value);
    else if (upperKey == QStringLiteral("MAXHEALTH"))
        table->setMaxHealth(value.toFloat());
    else if (upperKey == QStringLiteral("HEALTH"))
        table->setHealth(value.toFloat());
    else if (upperKey == QStringLiteral("HUNGER"))
        table->setHunger(value.toFloat());
    else if (upperKey == QStringLiteral("LEVEL"))
        table->setLevel(value.toFloat());
    else if (upperKey == QStringLiteral("WORLD"))
        table->setWorld(value);
}

void McscpAddon::playerEvent(const QString &type, const QString &uuid)
{
    const QString upperType = type.toUpper();

    if (upperType == QStringLiteral("PLAYERJOIN"))
        playerConnected(uuid);
    else if (upperType == QStringLiteral("PLAYERLEAVE"))
        playerDisconnected(uuid);
}

void McscpAddon::playerConnected(const QString &uuid)
{
    emit playerJoined(uuid.toUpper());
}

void McscpAddon::playerDisconnected(const QString &uuid)
{
    const QString upperUuid = uuid.toUpper();

    removePlayerTable(upperUuid);

    emit playerLeft(upperUuid);
}

void McscpAddon::messageEvent(const QString &type, const QString &uuid, const QString &message)
{
    const QString typeUpper = type.toUpper();

    if (typeUpper == QStringLiteral("CHAT"))
        chatMessage(uuid, message);
    else if (typeUpper == QStringLiteral("DEATH"))
        deathMessage(uuid, message);
}

void McscpAddon::chatMessage(const QString &uuid, const QString &message)
{
    const QString upperUuid = uuid.toUpper();

    emit chatEvent(upperUuid, message);
}

void McscpAddon::logEvent(int oldSize)
{
    emit newLogData(oldSize);
}

void McscpAddon::deathMessage(const QString &uuid, const QString &message)
{
    const QString upperUuid = uuid.toUpper();

    emit playerDied(upperUuid, message);
}
