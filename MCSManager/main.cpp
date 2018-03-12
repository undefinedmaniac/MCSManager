#include <QCoreApplication>
#include <QDebug>

#include "config/serverconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerConfig config("D:/QtProjects/build-MCSManager-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/config.ini");

    qDebug() << "Unexpected Shutdown Behavior: " << config.unexpectedShutdownBehavior();

    return a.exec();
}
