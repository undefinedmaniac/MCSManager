#include "minecraftserverbuilder.h"

MinecraftServerBuilder::MinecraftServerBuilder(IMinecraftServerAddonFactory *factory) :
    mFactory(factory)
{
}

IMinecraftServer *MinecraftServerBuilder::getServer(const IServerConfig *config)
{
    mServer.reset(new MinecraftServer(config));

    QStringList addons = config->enabledAddons();

    foreach (QString addon, addons) {
        IMinecraftServerAddon *serverAddon = mFactory->getAddon(addon, mServer.data());
        mServer->addAddon(serverAddon);
    }

    return mServer.data();
}

void MinecraftServerBuilder::setAddonFactory(IMinecraftServerAddonFactory *factory)
{
    mFactory = factory;
}

IMinecraftServerAddonFactory *MinecraftServerBuilder::addonFactory()
{
    return mFactory;
}
