#include "tcpliststreamclient.h"

TcpListStreamClient::TcpListStreamClient()
{
    connect(&mStream, SIGNAL(readyRead()), SLOT(readyRead()));

    connectToHost("127.0.0.1", 54620);

    mStream.setSocket(this);
}

void TcpListStreamClient::readyRead()
{
    if (mCount == 0)
        mTime = QTime::currentTime();

    mStream.readList();

    mCount++;

    if (mCount >= 1000000) {
        qDebug() << QStringLiteral("Received 1,000,000 lists!");
        qDebug() << QStringLiteral("You computer took %1 seconds!").arg(mTime.secsTo(QTime::currentTime()));
    }
}
