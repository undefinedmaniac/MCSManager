#include <QCoreApplication>
#include <QDebug>

#include "configfunctions.h"
#include "configfile.h"
#include "configmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigManager manager(joinPaths(a.applicationDirPath(), "configs"));
    ConfigHash defaults;
    defaults.insert("value1", "true");
    defaults.insert("value2", "false");
    manager.registerAddon("testAddon1", defaults);
    ConfigHash defaults2;
    defaults2.insert("value1", "10");
    defaults2.insert("pi", "3.14");
    manager.registerAddon("testAddon2", defaults2);
    manager.setAppPrimaryDefaults(defaults);
    manager.setServerPrimaryDefaults(defaults);
    manager.setServerBackupDefaults(defaults);
    manager.loadConfiguration();
    manager.getAddonConfig("server1", "testAddon2");

    qDebug() << manager.serverList();
    qDebug() << manager.getServerConfig("server1").enabledAddons->getEnabledAddons();

    return a.exec();
}
