#include "minecraftserverbuilder.h"

MinecraftServerBuilder::MinecraftServerBuilder(IMinecraftServerAddonFactory *factory) :
    mFactory(factory)
{
}

MinecraftServerBuilder::~MinecraftServerBuilder()
{
    deleteServer();
}

IMinecraftServer *MinecraftServerBuilder::getServer(const IServerConfig *config)
{
    deleteServer();

    mServer = new MinecraftServer(config);

    QStringList addons = config->enabledAddons();

    foreach (QString addon, addons) {
        IMinecraftServerAddon *serverAddon = mFactory->getAddon(addon, mServer);
        mServer->addAddon(serverAddon);
    }

    return mServer;
}

void MinecraftServerBuilder::setAddonFactory(IMinecraftServerAddonFactory *factory)
{
    mFactory = factory;
}

IMinecraftServerAddonFactory *MinecraftServerBuilder::addonFactory()
{
    return mFactory;
}

void MinecraftServerBuilder::deleteServer()
{
    if (mServer != nullptr) {
        QObject *object = dynamic_cast<QObject *>(mServer);

        if (object != nullptr)
            object->deleteLater();
        else
            delete mServer;
    }
}
