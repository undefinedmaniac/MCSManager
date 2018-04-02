#include <QCoreApplication>
#include <QDebug>

#include "configfunctions.h"
#include "configfile.h"
#include "configmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigManager manager;

    manager.registerAddon("testAddon1");
    manager.registerAddon("testAddon2");
    manager.loadConfiguration(joinPaths(a.applicationDirPath(), "configs"));

    return a.exec();
}
