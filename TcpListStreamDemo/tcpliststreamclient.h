#ifndef TCPLISTSTREAMCLIENT_H
#define TCPLISTSTREAMCLIENT_H

#include "tcpliststream.h"

#include <QTcpSocket>
#include <QTime>
#include <QDebug>

class TcpListStreamClient : public QTcpSocket
{
    Q_OBJECT
public:
    TcpListStreamClient();

private slots:
    void readyRead();

private:
    QTime mTime;
    TcpListStream mStream;
    int mCount = 0;
};

#endif // TCPLISTSTREAMCLIENT_H
