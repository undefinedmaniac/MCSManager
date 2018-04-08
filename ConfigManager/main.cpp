#include <QCoreApplication>
#include <QDebug>

#include "serverconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigData data0;

    data0.append(qMakePair(QString("test0"), QString("true")));
    data0.append(qMakePair(QString("test1"), QString("false")));

    ConfigData data1;

    data1.append(qMakePair(QString("test0"), QString("hi")));
    data1.append(qMakePair(QString("test1"), QString("yo")));

    ConfigData data2;

    data2.append(qMakePair(QString("test0"), QString("Im an addon")));
    data2.append(qMakePair(QString("test1"), QString("Im an addon")));

    QHash<QString, ConfigData> addonHash;

    addonHash.insert("Addon1", data2);

    ServerConfig server(a.applicationDirPath() + QStringLiteral("/configs/server1"), addonHash);

    server.initServerConfig(data0);
    server.initBackupConfig(data1);
    server.initEnabledAddons();

    return a.exec();
}
