#ifndef TCPLISTSTREAMSERVER_H
#define TCPLISTSTREAMSERVER_H

#include "tcpliststream.h"

#include <QTcpServer>
#include <QDebug>
#include <QTcpSocket>

class TcpListStreamServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpListStreamServer();

private slots:
    void newConnection();
};

#endif // TCPLISTSTREAMSERVER_H
