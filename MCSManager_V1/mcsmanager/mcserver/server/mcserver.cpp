#include "mcserver.h"

McServer::McServer(IServerConfig *config, IMcsManagerCore *core, QObject *parent) :
    IMcServer(parent), McsManagerCoreChild(core), mConfig(config)
{
    ServerConfigReader reader(config->getServerConfig());

    mProcess.setProgram(reader.javaPath());
    mProcess.setWorkingDirectory(reader.workingDirectory());

    QStringList arguments;
    arguments.append(QStringLiteral("-jar"));
    arguments.append(reader.jarName());
    arguments.append(reader.arguments());
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

    foreach (IMcServerAddon *addon, mAddons)
        deleteAddon(addon);
}

QString McServer::getName() const
{
    return mConfig->getServerName();
}

IServerConfig *McServer::getConfig()
{
    return mConfig;
}

void McServer::addAddon(IMcServerAddon *addon)
{
    if (!addon)
        return;

    mAddons.insert(addon->getName(), addon);
}

void McServer::removeAddon(const QString &addonName)
{
    mAddons.remove(addonName);
}

IMcServerAddon *McServer::getAddon(const QString &addonName)
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

IMcsManagerCore *McServer::getCore()
{
    return McsManagerCoreChild::getCore();
}

IConfigManager *McServer::getConfigManager()
{
    return McsManagerCoreChild::getConfigManager();
}

IBackupManager *McServer::getBackupManager()
{
    return McsManagerCoreChild::getBackupManager();
}

IMcServerBuilder *McServer::getServerBuilder()
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
                case ConfigGlobal::DoNothing:
                    break;
                case ConfigGlobal::Restart:
                    qDebug() << "Restarting!";
                    start();
                    break;
                case ConfigGlobal::StartAltServer:
                    if (IMcsManagerCore *core = getCore())
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
    if (mIsRealServer) {
        IMcscpAddon *addon = dynamic_cast<IMcscpAddon*>(getAddon(QStringLiteral("mcscp")));
        if (addon) {
            addon->stopServer();
            return;
        }
    }

    mProcess.kill();
}

void McServer::initAddons()
{
    foreach (IMcServerAddon *addon, mAddons)
        addon->preInit();

    foreach (IMcServerAddon *addon, mAddons)
        addon->init();
}

void McServer::startAddons()
{
    foreach (IMcServerAddon *addon, mAddons)
        addon->start();
}

void McServer::stopAddons()
{
    foreach (IMcServerAddon *addon, mAddons)
        addon->stop();
}

void McServer::deleteAddon(IMcServerAddon *addon)
{
    if (QObject *object = dynamic_cast<QObject *>(addon))
        object->deleteLater();
    else
        delete addon;
}
