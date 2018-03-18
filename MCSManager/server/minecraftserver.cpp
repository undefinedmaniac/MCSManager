#include "minecraftserver.h"

MinecraftServer::MinecraftServer(const IServerConfig *config) : mConfig(config)
{
    connect(&mProcess, &QProcess::started, this, &MinecraftServer::serverStarted);
    connect(&mProcess, SIGNAL(finished(int)), this, SLOT(serverStopped()));
    connect(&mProcess, &QProcess::readyReadStandardOutput,
            this, &MinecraftServer::readyReadStandardOutput);
    connect(&mProcess, &QProcess::readyReadStandardError,
            this, &MinecraftServer::readyReadStandardError);
    connect(&mProcess, &QProcess::bytesWritten, this, &MinecraftServer::bytesWritten);
    connect(&mProcess, &QProcess::errorOccurred, this, &MinecraftServer::errorOccurred);

    mProcess.setProgram(config->javaPath());
    mProcess.setWorkingDirectory(config->workingDirectory());

    QStringList arguments;
    arguments.append(QStringLiteral("-jar"));
    arguments.append(config->jarName());
    arguments.append(config->arguments());

    mProcess.setArguments(arguments);
}

MinecraftServer::~MinecraftServer()
{
    if (isRunning())
        stop();

    foreach (IMinecraftServerAddon *addon, mAddons){
        QObject *object = dynamic_cast<QObject *>(addon);

        if (object != nullptr)
            object->deleteLater();
        else
            delete addon;

    }

    qDebug() << "Minecraft server deleted!";
}

void MinecraftServer::setServerManager(IMinecraftServerManager *serverManager)
{
    mServerManager = serverManager;
}

IMinecraftServerManager *MinecraftServer::serverManager()
{
    return mServerManager;
}

const IServerConfig *MinecraftServer::config() const
{
    return mConfig;
}

void MinecraftServer::start()
{
    mProcess.open();
}

void MinecraftServer::stop()
{
    if (mConfig->isRealServer()) {
        const QString stopCommand = QStringLiteral("help");
        write(stopCommand.toUtf8());

        if (!mProcess.waitForFinished(10000)) {
            killServer();
        }
    } else {
        killServer();
    }
}

bool MinecraftServer::isRunning() const
{
    return (mProcess.state() == QProcess::Running);
}

QByteArray MinecraftServer::readAllStandardOutput()
{
    return mProcess.readAllStandardOutput();
}

QByteArray MinecraftServer::readAllStandardError()
{
    return mProcess.readAllStandardError();
}

int MinecraftServer::write(const QByteArray &data)
{   
    return mProcess.write(data);
}

void MinecraftServer::addAddon(IMinecraftServerAddon *addon)
{
    if (addon == nullptr)
        return;

    qDebug() << "Addon added: " << addon->name();
    mAddons.insert(addon->name(), addon);
}

void MinecraftServer::removeAddon(const QString &name)
{
    mAddons.remove(name);
}

QStringList MinecraftServer::addons() const
{
    return mAddons.keys();
}

IMinecraftServerAddon *MinecraftServer::getAddon(const QString &name)
{
    return mAddons.value(name);
}

IMinecraftServerAddon *MinecraftServer::getAddon(const QString &name) const
{
    return mAddons.value(name);
}

void MinecraftServer::startAddons()
{
    foreach (IMinecraftServerAddon *addon, mAddons) {
        addon->start();
    }
}

void MinecraftServer::stopAddons()
{
    foreach (IMinecraftServerAddon *addon, mAddons) {
        addon->stop();
    }
}

void MinecraftServer::errorOccurred(QProcess::ProcessError errorType)
{
    QString errorString;

    switch (errorType) {
    case QProcess::FailedToStart:
        errorString = QStringLiteral("Error: Server failed to start!");
    case QProcess::Crashed:
        errorString = QStringLiteral("Error: Server crashed!");
    case QProcess::Timedout:
        errorString = QStringLiteral("Error: Server timed out!");
    case QProcess::WriteError:
        errorString = QStringLiteral("Error: Write error while writing to the server io!");
    case QProcess::ReadError:
        errorString = QStringLiteral("Error: Read error while reading from the server io!");
    default:
        errorString = QStringLiteral("Error: Unknown error!");
    }

    emit error(errorString);
}

void MinecraftServer::serverStarted()
{
    qDebug() << "Server [" << mConfig->name() << "] started!";
    startAddons();
    emit started();
}

void MinecraftServer::serverStopped()
{
    qDebug() << "Server [" << mConfig->name() << "] stopped!";
    stopAddons();
    emit stopped();
}

void MinecraftServer::killServer()
{
    mProcess.kill();
    mProcess.waitForFinished(-1);
}
