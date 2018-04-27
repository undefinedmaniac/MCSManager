#include <QCoreApplication>

#include "mcsmanager/mcsmanagerapplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Application::McsManagerApplication application;

    application.start();

    return a.exec();
}
