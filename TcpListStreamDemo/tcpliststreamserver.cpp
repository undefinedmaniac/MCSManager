#include "tcpliststreamserver.h"

TcpListStreamServer::TcpListStreamServer()
{
    connect(this, SIGNAL(newConnection()), SLOT(newConnection()));

    listen(QHostAddress("127.0.0.1"), 54620);
}

void TcpListStreamServer::newConnection()
{
    TcpListStream stream;
    stream.setSocket(nextPendingConnection());

    for (int i = 0; i < 1000000; i++) {
        QStringList list;

        list.append(QString::number(i));
        list.append(QString::number(i + 1));
        list.append(QString::number(i - 1));

        stream.writeList(list);
    }
}
