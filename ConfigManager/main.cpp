#include <QCoreApplication>
#include <QDebug>

#include "configmanager.h"

void testFunc() {
    ConfigData data0;

    data0.append(qMakePair(QString("test0"), QString("true")));
    data0.append(qMakePair(QString("test1"), QString("false")));

    ConfigData data1;

    data1.append(qMakePair(QString("test0"), QString("hi")));
    data1.append(qMakePair(QString("test1"), QString("yo")));

    ConfigData data2;

    data2.append(qMakePair(QString("test0"), QString("Im an addon")));
    data2.append(qMakePair(QString("test1"), QString("Im an addon")));

    ConfigManager manager;

    manager.setAppConfigDefaults(data0);
    manager.setServerConfigDefaults(data1);
    manager.setBackupConfigDefaults(data2);
    manager.registerAddon("Addon1", data2);
    manager.loadConfigs(QCoreApplication::applicationDirPath() + QStringLiteral("/config"));

    qDebug() << "Server List: " << manager.getServerList();
    qDebug() << manager.getServerConfig("server1")->getEnabledAddons();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testFunc();

    return a.exec();
}
