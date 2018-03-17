#include "mcsmanagercore.h"

McsManagerCore::McsManagerCore(IConfigManager *configManager, IMinecraftServerBuilder *serverBuilder,
                               IMinecraftServerAddonFactory *addonFactory, IMinecraftServerManager *serverManager) :
    mConfigManager(configManager), mServerBuilder(serverBuilder), mAddonFactory(addonFactory), mServerManager(serverManager)
{
    configManager->setCore(this);
    serverBuilder->setCore(this);
    serverManager->setCore(this);
    serverBuilder->setAddonFactory(addonFactory);
}

void McsManagerCore::startApplication()
{
    mConfigManager->loadConfig(QCoreApplication::applicationDirPath() + QStringLiteral("/config"));

    const IGeneralConfig *generalConfig = mConfigManager->getGeneralConfig();

    startServer(generalConfig->defaultServer());
}

QStringList McsManagerCore::serverList() const
{
    return mConfigManager->serverList();
}

QStringList McsManagerCore::backupList(const QString &serverName) const
{

}

const IServerConfig *McsManagerCore::getServerConfig(const QString &serverName) const
{
    return mConfigManager->getServerConfig(serverName);
}

void McsManagerCore::startServer(const QString &serverName)
{
    if (isRunning())
        forceStop();

    const IServerConfig *config = getServerConfig(serverName);

    if (config == nullptr)
        return;

    IMinecraftServer *server = mServerBuilder->getServer(config);

    mServerManager->setServer(server);

    mServerManager->startServer();
}

void McsManagerCore::runBackup(const QString &serverName)
{

}

QString McsManagerCore::name() const
{
    IMinecraftServer *server = mServerManager->server();

    if (server == nullptr)
        return QStringLiteral("");

    return server->config()->name();
}

bool McsManagerCore::isRunning() const
{
    IMinecraftServer *server = mServerManager->server();

    if (server == nullptr)
        return false;

    return server->isRunning();
}

const IServerConfig *McsManagerCore::config() const
{
    IMinecraftServer *server = mServerManager->server();

    if (server == nullptr)
        return nullptr;

    server->config();
}

void McsManagerCore::sendChatMsg(const QString &playerName, const QByteArray &message)
{

}

void McsManagerCore::sendMcscpCmd(IMcscpCommand *cmd)
{

}

QByteArray McsManagerCore::readAllLogData() const
{

}

QByteArray McsManagerCore::readNewLogData()
{

}

void McsManagerCore::stop()
{
    //QTimer::singleShot(300000, this, SLOT(forceStop()));
}

void McsManagerCore::forceStop()
{
    mServerManager->stopServer();
}

void McsManagerCore::restart()
{
    //QTimer::singleShot(300000, this, SLOT(forceRestart()));
}

void McsManagerCore::forceRestart()
{
    mServerManager->stopServer(IServerManagerConfig::RestartServer);
}
