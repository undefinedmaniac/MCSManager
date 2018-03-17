#include <QCoreApplication>

#include "core/mcsmanagercore.h"

#include "config/configmanager.h"

#include "server/builder/minecraftserverbuilder.h"
#include "server/manager/minecraftservermanager.h"
#include "server/addons/minecraftserveraddonfactory.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigManager configManager;

    MinecraftServerBuilder serverBuilder;

    MinecraftServerAddonFactory addonFactory;

    MinecraftServerManager serverManager;

    McsManagerCore core(&configManager, &serverBuilder, &addonFactory, &serverManager);

    core.startApplication();

    return a.exec();
}
