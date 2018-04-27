#include "mcserver.h"

using Server::McServer;

McServer::McServer(Config::IServerConfig *config, Core::IMcsManagerCore *core, QObject *parent) :
    IMcServer(parent), McsManagerCoreChild(core), mConfig(config)
{
    Server::ServerConfigReader reader(config->getServerConfig());

    mProcess.setProgram(reader.javaPath());
    mProcess.setWorkingDirectory(reader.workingDirectory());

    QStringList arguments;
    arguments.append(reader.beforeArguments());
    arguments.append(QStringLiteral("-jar"));
    arguments.append(reader.jarName());
    arguments.append(reader.afterArguments());
    mProcess.setArguments(arguments);

    mIsRealServer = reader.isRealServer();
    mShutdownBehavior = reader.unexpectedShutdownBehavior();
    mAltServer = reader.alternativeServer();

    connect(&mProcess, SIGNAL(started()), SLOT(serverStarted()));
    connect(&mProcess, SIGNAL(finished(int, QProcess::ExitStatus)), SLOT(serverStopped(int, QProcess::ExitStatus)));
    connect(&mProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), SLOT(serverErrorOccurred(QProcess::ProcessError)));
}

McServer::~McServer()
{
    if (isRunning()) {
        stop();
        mProcess.waitForFinished(-1);
    }

    foreach (Addon::IMcServerAddon *addon, mAddons)
        deleteAddon(addon);
}

QString McServer::getName() const
{
    return mConfig->getServerName();
}

Config::IServerConfig *McServer::getConfig()
{
    return mConfig;
}

void McServer::addAddon(Addon::IMcServerAddon *addon)
{
    if (!addon)
        return;

    mAddons.insert(addon->getName(), addon);
}

void McServer::removeAddon(const QString &addonName)
{
    mAddons.remove(addonName);
}

Addon::IMcServerAddon *McServer::getAddon(const QString &addonName)
{
    return mAddons.value(addonName, nullptr);
}

QStringList McServer::getAddonList() const
{
    return mAddons.keys();
}

void McServer::start()
{
    if (isRunning())
        return;

    if (mFirstStart) {
        mFirstStart = false;
        initAddons();
    }

    mState = Starting;
    mProcess.open();
}

void McServer::restart()
{
    if (isRunning()) {
        mState = Restarting;
        stopServer();
    } else {
        start();
    }
}

void McServer::stop()
{
    if (!isRunning())
        return;

    mState = Stopping;
    stopServer();
}

bool McServer::isRunning() const
{
    return (mProcess.state() == QProcess::Running);
}

Core::IMcsManagerCore *McServer::getCore()
{
    return McsManagerCoreChild::getCore();
}

Config::IConfigManager *McServer::getConfigManager()
{
    return McsManagerCoreChild::getConfigManager();
}

Backup::IBackupManager *McServer::getBackupManager()
{
    return McsManagerCoreChild::getBackupManager();
}

Server::IMcServerBuilder *McServer::getServerBuilder()
{
    return McsManagerCoreChild::getServerBuilder();
}

void McServer::serverStarted()
{
    qDebug() << "Server Started!";
    mState = Started;
    startAddons();
    emit started();
}

void McServer::serverStopped(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Server Stopped!";
    Q_UNUSED(exitCode);

    stopAddons();

    bool expected = (mState == Stopping || mState == Restarting);

    if (mState == Restarting) {
        start();
    } else {
        mState = Stopped;

        if (!expected) {
            qDebug() << "Unexpected stop!";
            if (exitStatus == QProcess::CrashExit) {
                qDebug() << "Crash Exit!";
                start();
            } else {
                switch (mShutdownBehavior) {
                case Config::DoNothing:
                    break;
                case Config::Restart:
                    qDebug() << "Restarting!";
                    start();
                    break;
                case Config::StartAltServer:
                    if (Core::IMcsManagerCore *core = getCore())
                        core->startServer(mAltServer);
                    break;
                }
            }
        }
    }

    emit stopped(expected);
}

void McServer::serverErrorOccurred(QProcess::ProcessError errorType)
{
    QString errorMessage;

    switch (errorType) {
    case QProcess::FailedToStart:
        errorMessage = QStringLiteral("ERROR: Server failed to start!");
        break;
    case QProcess::Crashed:
        errorMessage = QStringLiteral("ERROR: Server crashed!");
        break;
    case QProcess::Timedout:
        errorMessage = QStringLiteral("ERROR: Server timed out!");
        break;
    case QProcess::WriteError:
        errorMessage = QStringLiteral("ERROR: Could not send data to server!");
        break;
    case QProcess::ReadError:
        errorMessage = QStringLiteral("ERROR: Could not read data from the server!");
        break;
    case QProcess::UnknownError:
        errorMessage = QStringLiteral("ERROR: Unknown error");
        break;
    default:
        errorMessage = QStringLiteral("");
        break;
    }

    emit error(errorMessage);
}

void McServer::stopServer()
{
    using Mcscp::IMcscpAddon;

    if (mIsRealServer) {
        IMcscpAddon *addon = dynamic_cast<IMcscpAddon*>(getAddon(Mcscp::ADDON_NAME));
        if (addon && addon->isConnected()) {
            addon->stopServer();
            return;
        }
    }

    mProcess.kill();
}

void McServer::initAddons()
{
    foreach (Addon::IMcServerAddon *addon, mAddons)
        addon->preInit();

    foreach (Addon::IMcServerAddon *addon, mAddons)
        addon->init();
}

void McServer::startAddons()
{
    foreach (Addon::IMcServerAddon *addon, mAddons)
        addon->start();
}

void McServer::stopAddons()
{
    foreach (Addon::IMcServerAddon *addon, mAddons)
        addon->stop();
}

void McServer::deleteAddon(Addon::IMcServerAddon *addon)
{
    if (QObject *object = dynamic_cast<QObject *>(addon))
        object->deleteLater();
    else
        delete addon;
}
