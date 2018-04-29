#include "commandline.h"

using Cli::CommandLine;

CommandLine::CommandLine(QObject *parent) : QObject(parent)
{
    connect(&mReader, SIGNAL(newCommand(QString)), SLOT(newCommand(QString)), Qt::BlockingQueuedConnection);
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), &mReader, SLOT(stopRunning()), Qt::QueuedConnection);
}

void CommandLine::start(Core::IMcsManagerCore *core)
{
    if (!core)
        return;

    mCore = core;

    connect(core, SIGNAL(currentServerChanged()), SLOT(currentServerChanged()));
    connect(core, SIGNAL(backupStarted(QString)), SLOT(backupStarted(QString)));
    connect(core, SIGNAL(backupFinished(QString)), SLOT(backupFinished(QString)));
    connect(core, SIGNAL(backupError(QString, QString)), SLOT(backupError(QString, QString)));

    setMode(Standard);
    mWriter.writePrefix();
    mReader.start();
}

void CommandLine::newCommand(QString command)
{
    mIsRunningCommand = true;
    processCommand(command);
    mWriter.writePrefix();
    mIsRunningCommand = false;
}

void CommandLine::backupStarted(QString server)
{

}

void CommandLine::backupFinished(QString server)
{

}

void CommandLine::backupError(QString server, QString errorString)
{

}

void CommandLine::currentServerChanged()
{
    Server::IMcServer *server = mCore->getCurrentServer();

    mServer = server;

    if (server) {
        connect(server, SIGNAL(started()), SLOT(serverStarted()));
        connect(server, SIGNAL(stopped(bool)), SLOT(serverStopped(bool)));
        connect(server, SIGNAL(error(QString)), SLOT(serverError(QString)));

        mAddon = dynamic_cast<Mcscp::IMcscpAddon*>(server->getAddon(Mcscp::ADDON_NAME));

        if (mAddon)
            connect(mAddon, SIGNAL(newLogData(int)), SLOT(newLogData(int)));

    } else {
        mAddon = nullptr;
    }
}

void CommandLine::serverStarted()
{
    if (mMode == Standard) {
        const QString serverName = mServer->getName();
        QString message;
        message += QStringLiteral("Server ");
        message += serverName;
        message += QStringLiteral(" has started!");
        interruptPrint(message);
    }
}

void CommandLine::serverStopped(bool expected)
{
    if (mMode == Standard) {
        const QString serverName = mServer->getName();
        QString message;
        message += QStringLiteral("Server ");
        message += serverName;

        if (expected)
            message += QStringLiteral(" has stopped!");
        else
            message += QStringLiteral(" has stopped unexpectedly!");

        interruptPrint(message);
    } else {
        setMode(Standard);
        interruptPrint(getError(ConsoleClosed));
    }
}

void CommandLine::serverError(QString errorString)
{
    if (mMode == Standard) {
        const QString serverName = mServer->getName();
        QString message;
        message += QStringLiteral("Server ");
        message += serverName;
        message += QStringLiteral(" has encountered an error: ");
        message += errorString;
        interruptPrint(message);
    }
}

void CommandLine::newLogData(int startingPos)
{
    if (mMode == Console) {
        const QString data = mAddon->readLogFromPos(startingPos);
        interruptPrint(data);
    }
}

void CommandLine::setMode(CommandLine::Mode mode)
{
    mMode = mode;
    mWriter.setPrefix(getPrefix());
}

QString CommandLine::getPrefix() const
{
    switch (mMode) {
    case Standard:
        return QStringLiteral("Standard");
    case Console:
        return QStringLiteral("Console");
    default:
        return QStringLiteral("");
    }
}

QString CommandLine::getError(CommandLine::ErrorType type)
{
    switch (type) {
    case ConsoleClosed:
        return QStringLiteral("Server console closed: Switching to Standard mode");
    case InvalidMode:
        return QStringLiteral("Invalid mode specified, use either Standard or Console");
    case ConsoleModeUnavailable:
        return QStringLiteral("Console mode unavailable for the current server: MCSCP is disabled");
    case InvalidCommand:
        return QStringLiteral("Invalid command, type help to view all commands");
    case ListItemNotSpecified:
        return QStringLiteral("No item specified, use servers, addons, or players");
    case NoServersFound:
        return QStringLiteral("No servers found");
    case ServerInvalid:
        return QStringLiteral("The specified server is invalid. Note that server names are case-sensitive");
    case NoCurrentServer:
        return QStringLiteral("There is no current server");
    case NoAddonsFound:
        return QStringLiteral("No addons found");
    case CannotPrintPlayers:
        return QStringLiteral("Cannot print players for the server: MCSCP is disabled or disconnected");
    case NoPlayersOnline:
        return QStringLiteral("There are no players on the server");
    case NoServerSpecified:
        return QStringLiteral("No server specified");
    case ServerNotRunning:
        return QStringLiteral("There is no running server");
    default:
        return QStringLiteral("Unknown error");
    }
}

void CommandLine::processCommand(const QString &command)
{
    const QStringList parts = command.split(' ');
    const QStringList parameters = parts.mid(1);
    const QString type = parts.first().toUpper();

    if (type == QStringLiteral("MODE")) {
        changeMode(parameters);
    } else {
        //Pass the command onward
        switch (mMode) {
        case Standard:
            processStandardCommand(type, parameters);
            break;
        case Console:
            processConsoleCommand(command);
            break;
        default:
            break;
        }
    }
}

void CommandLine::changeMode(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(getError(InvalidMode));
        return;
    }

    const QString mode = parameters.first().toUpper();
    if (mode == QStringLiteral("STANDARD")) {
        setMode(Standard);
    } else if (mode == QStringLiteral("CONSOLE")) {
        if (!mServer) {
            mWriter.writeLine(getError(NoCurrentServer));
            return;
        }

        if (!mServer->isRunning()) {
            mWriter.writeLine(getError(ServerNotRunning));
            return;
        }

        if (!mAddon) {
            mWriter.writeLine(getError(ConsoleModeUnavailable));
            return;
        }
        setMode(Console);
    }
}

void CommandLine::processStandardCommand(const QString &type, const QStringList &parameters)
{
    if (type == QStringLiteral("LIST"))
        listCommand(parameters);
    else if (type == QStringLiteral("START"))
        startCommand(parameters);
    else if (type == QStringLiteral("STOP"))
        stopCommand();
    else if (type == QStringLiteral("RESTART"))
        restartCommand();
    else if (type == QStringLiteral("EXIT"))
        QCoreApplication::quit();
    else
        mWriter.writeLine(getError(InvalidCommand));
}

void CommandLine::listCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(getError(ListItemNotSpecified));
        return;
    }

    const QString item = parameters.first().toUpper();

    if (item == QStringLiteral("SERVERS")) {
        const QStringList servers = mCore->getServerList();

        if (servers.isEmpty())
            mWriter.writeLine(getError(NoServersFound));
        else
            mWriter.writeLines(servers);
    } else if (item == QStringLiteral("ADDONS")) {
        Config::IServerConfig *serverConfig;

        if (parameters.size() >= 2) {
            const QString object = parameters.at(1);
            serverConfig = mCore->getServerConfig(object);
            if (!serverConfig) {
                mWriter.writeLine(getError(ServerInvalid));
                return;
            }
        } else {
            if (!mServer) {
                mWriter.writeLine(getError(NoCurrentServer) + QStringLiteral(". Start a server or specify a server name"));
                return;
            }
            serverConfig = mServer->getConfig();
        }

        const QStringList enabledAddons = serverConfig->getEnabledAddons();
        if (enabledAddons.isEmpty())
            mWriter.writeLine(getError(NoAddonsFound));
        else
            mWriter.writeLines(enabledAddons);
    } else if (item == QStringLiteral("PLAYERS")) {
        if (!mServer) {
            mWriter.writeLine(getError(NoCurrentServer));
            return;
        }
        if(!mAddon || !mAddon->isConnected()) {
            mWriter.writeLine(getError(CannotPrintPlayers));
            return;
        }

        const QStringList playerList = mAddon->getPlayerList();
        if (playerList.isEmpty())
            mWriter.writeLine(getError(NoPlayersOnline));
        else
            mWriter.writeLines(playerList);
    }
}

void CommandLine::startCommand(const QStringList &parameters)
{   
    if (parameters.isEmpty()) {
        if (!mServer) {
            mWriter.writeLine(getError(NoServerSpecified));
            return;
        }
        mServer->start();
        return;
    }

    const QString serverName = parameters.first();
    if (!mCore->getServerList().contains(serverName)) {
        mWriter.writeLine(getError(ServerInvalid));
        return;
    }

    mCore->startServer(serverName);
}

void CommandLine::stopCommand()
{
    if (!mServer) {
        mWriter.writeLine(getError(NoCurrentServer));
        return;
    }

    if (!mServer->isRunning()) {
        mWriter.writeLine(getError(ServerNotRunning));
        return;
    }

    mServer->stop();
}

void CommandLine::restartCommand()
{
    if (!mServer) {
        mWriter.writeLine(getError(NoCurrentServer));
        return;
    }

    mServer->restart();
}

void CommandLine::processConsoleCommand(const QString &command)
{
    if (mAddon && mAddon->isConnected())
        mAddon->sendToConsole(command);
}

void CommandLine::interruptPrint(const QString &line)
{
    mWriter.erasePrefix();
    mWriter.writeLine(line);

    if (!mIsRunningCommand)
        mWriter.writePrefix();
}
