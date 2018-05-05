#include "commandline.h"

using Cli::CommandLine;

CommandLine::CommandLine(QObject *parent) : QObject(parent)
{
    connect(&mReader, SIGNAL(newCommand(QString)), SLOT(newCommand(QString)), Qt::BlockingQueuedConnection);
    connect(&mReader, SIGNAL(started()), SIGNAL(started()));
    connect(&mReader, SIGNAL(stopped()), SIGNAL(stopped()));
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

void CommandLine::stop()
{
    mLog.clear();
    mReader.stop();
}

void CommandLine::newCommand(QString command)
{
    mIsRunningCommand = true;
    processCommand(command.trimmed());

    if (!mHasRequestedQuit)
        mWriter.writePrefix();

    mIsRunningCommand = false;
}

void CommandLine::backupStarted(QString server)
{
    if (mMode == Standard) {
        QString message;
        message += QStringLiteral("Backing up ");
        message += server;
        message += QStringLiteral("...");
        interruptPrint(message);
    }
}

void CommandLine::backupFinished(QString server)
{
    if (mMode == Standard) {
        QString message;
        message += QStringLiteral("Finished backing up ");
        message += server;
        interruptPrint(message);
    }
}

void CommandLine::backupError(QString server, QString errorString)
{
    if (mMode == Standard) {
        QString message;
        message += QStringLiteral("Error while backing up ");
        message += server;
        message += QStringLiteral(": ");
        message += errorString;
        interruptPrint(message);
    }
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
    case ServerAlreadyRunning:
        return QStringLiteral("The server is already running!");
    case NoActionSpecified:
        return QStringLiteral("No action specified, use run or view");
    case NoBackupsFound:
        return QStringLiteral("No backups found");
    case InvalidObject:
        return QStringLiteral("Invalid object");
    case InvalidAction:
        return QStringLiteral("Invalid action");
    case NoObjectSpecified:
        return QStringLiteral("No object specified");
    case CannotPrintLog:
        return QStringLiteral("Cannot print server log: MCSCP is disabled");
    case ServerLogEmpty:
        return QStringLiteral("The server log is empty");
    case AppLogEmpty:
        return QStringLiteral("The app log is empty");
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
    else if (type == QStringLiteral("BACKUP"))
        backupCommand(parameters);
    else if (type == QStringLiteral("PRINT"))
        printCommand(parameters);
    else if (type == QStringLiteral("EXIT")) {
        mHasRequestedQuit = true;
        mReader.stop();
        QTimer::singleShot(0, this, SIGNAL(exitApplication()));
    }
    else
        mWriter.writeLine(getError(InvalidCommand));
}

void CommandLine::listCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(getError(NoObjectSpecified) + QStringLiteral(". Use Servers, Addons, or Players"));
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
                mWriter.writeLine(getError(NoCurrentServer) +
                                  QStringLiteral(". Start a server or specify a server name"));
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
    } else {
        mWriter.writeLine(getError(InvalidObject) + QStringLiteral(". Use Servers, Addons, or Players"));
    }
}

void CommandLine::startCommand(const QStringList &parameters)
{
    //If no server is specified, see if we can work with our current one
    if (parameters.isEmpty()) {        
        if (!mServer) {
            mWriter.writeLine(getError(NoServerSpecified));
            return;
        }

        if (mServer->isRunning()) {
            mWriter.writeLine(getError(ServerAlreadyRunning));
            return;
        }

        mServer->start();
        return;
    }

    //If a server is specified, see if it is our current one
    const QString serverName = parameters.first();
    if (mServer && mServer->getName() == serverName) {
        if (mServer->isRunning()) {
            mWriter.writeLine(getError(ServerAlreadyRunning));
            return;
        }

        mServer->start();
        return;
    }

    //If a server is specified but it isn't our current one
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

void CommandLine::backupCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(getError(NoActionSpecified));
        return;
    }

    const QString action = parameters.first().toUpper();
    QString serverName;

    if (parameters.size() >= 2) {
        serverName = parameters.at(1);
    } else {
        if (!mServer) {
            mWriter.writeLine(getError(NoCurrentServer) +
                              QStringLiteral(". Start a server or specify a server name"));
            return;
        }

        serverName = mServer->getName();
    }

    if (!mCore->getServerList().contains(serverName)) {
        mWriter.writeLine(getError(ServerInvalid));
        return;
    }

    if (action == QStringLiteral("RUN")) {
        Backup::IBackupProcess *process = mCore->getBackupProcess(serverName);
        process->start();
    } else if (action == QStringLiteral("VIEW")) {
        const QStringList backupList = mCore->getBackupList(serverName);
        if (backupList.isEmpty())
            mWriter.writeLine(getError(NoBackupsFound));
        else
            mWriter.writeLines(backupList);
    } else {
        mWriter.writeLine(getError(InvalidAction) + QStringLiteral(". Use Run or View"));
    }
}

void CommandLine::printCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(getError(NoObjectSpecified) + QStringLiteral(". Use ServerLog or AppLog"));
        return;
    }

    const QString object = parameters.first().toUpper();
    if (object == QStringLiteral("SERVERLOG")) {        
        if (!mServer) {
            mWriter.writeLine(getError(NoCurrentServer));
            return;
        }

        if (!mAddon) {
            mWriter.writeLine(getError(NoCurrentServer));
            return;
        }

        const QString log = mAddon->readEntireLog();
        if (log.isEmpty())
            mWriter.writeLine(getError(ServerLogEmpty));
        else
            mWriter.writeLine(log);
    } else if (object == QStringLiteral("APPLOG")) {
        if (mLog.isEmpty())
            mWriter.writeLine(getError(AppLogEmpty));
        else
            mWriter.writeLine(mLog);
    } else {
        mWriter.writeLine(getError(InvalidObject) + QStringLiteral(". Use ServerLog or AppLog"));
    }
}

void CommandLine::processConsoleCommand(const QString &command)
{
    if (mAddon && mAddon->isConnected())
        mAddon->sendToConsole(command);
}

void CommandLine::interruptPrint(const QString &line)
{
    mLog.append(line + '\n');

    mWriter.erasePrefix();
    mWriter.writeLine(line);

    if (!mIsRunningCommand && !mHasRequestedQuit)
        mWriter.writePrefix();
}
