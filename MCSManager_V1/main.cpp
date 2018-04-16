#include <QCoreApplication>

#include "mcsmanager/config/configfile.h"
#include "mcsmanager/config/serverconfig.h"
#include "mcsmanager/mcserver/server/serverconfigreader.h"
#include "mcsmanager/mcserver/server/mcserver.h"
#include "mcsmanager/mcserver/addons/sleeperaddon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerConfig config(joinPaths(QCoreApplication::applicationDirPath(), QStringLiteral("test")));
    config.initServerConfig(ServerConfigReader::getDefaults());

    McServer server(&config);

    server.addAddon(new SleeperAddon(&server));

    server.start();

    return a.exec();
}
