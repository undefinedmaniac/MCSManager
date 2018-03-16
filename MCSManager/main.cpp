#include <QCoreApplication>
#include <QDebug>

#include "config/serverconfig.h"
#include "config/generalconfig.h"

#include "config/configmanager.h"

#include "server/minecraftserver.h"

#include "core/mcsmanagercore.h"
#include "server/manager/minecraftservermanager.h"
#include "server/addons/logreader.h"

/*void testFunc() {
    ConfigManager manager;

    manager.loadConfig(QCoreApplication::applicationDirPath() + QStringLiteral("/config"));

    qDebug() << "Server List: " << manager.serverList();

    const IServerConfig *config = manager.getServerConfig(manager.getGeneralConfig()->defaultServer());

    if (config == nullptr)
        return;

    qDebug() << "Name: " << config->name();
    qDebug() << "Enabled Addons: " << config->enabledAddons();
    qDebug() << "Shutdown Behavior: " << config->unexpectedShutdownBehavior();
}*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    McsManagerCore core;

    MinecraftServerManager serverManager;

    serverManager.setCore(&core);

    ConfigManager configManager;

    configManager.loadConfig(QCoreApplication::applicationDirPath() + QStringLiteral("/config"));

    const IServerConfig *config = configManager.getServerConfig(configManager.getGeneralConfig()->defaultServer());

    if (config != nullptr) {
        MinecraftServer *server = new MinecraftServer(config);

        LogReader *logReader = new LogReader(QStringLiteral("logReader"), server);

        server->addAddon(logReader);

        serverManager.setConfig(config);

        serverManager.setServer(server);
        serverManager.startServer();
    }

    return a.exec();
}
