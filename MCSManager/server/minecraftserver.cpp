#include "minecraftserver.h"

MinecraftServer::MinecraftServer(const IServerConfig *config) : mConfig(config)
{
    connect(&mProcess, &QProcess::started, this, &MinecraftServer::started);
    connect(&mProcess, SIGNAL(finished(int)), this, SIGNAL(stopped()));
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
    mProcess.terminate();

    if (!mProcess.waitForFinished(5000))
        mProcess.kill();
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
