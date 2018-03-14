#include <QCoreApplication>
#include <QDebug>

#include "config/serverconfig.h"
#include "config/generalconfig.h"

#include "config/configmanager.h"

#include "server/minecraftserver.h"

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

    ConfigManager configManager;

    configManager.loadConfig(QCoreApplication::applicationDirPath() + QStringLiteral("/config"));

    const IServerConfig *config = configManager.getServerConfig(configManager.getGeneralConfig()->defaultServer());

    MinecraftServer *server;

    if (config != nullptr) {
        server = new MinecraftServer(config);
        server->start();
    }

    return a.exec();
}
