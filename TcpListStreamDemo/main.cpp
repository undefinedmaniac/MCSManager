#include "tcpliststreamserver.h"
#include "tcpliststreamclient.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TcpListStreamServer server;
    TcpListStreamClient client;

    return app.exec();
}
