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

void CommandLine::waitForStop()
{
    if (mReader.isRunning()) {
        QEventLoop loop;
        connect(&mReader, SIGNAL(stopped()), &loop, SLOT(quit()));
        loop.exec();
    }
}

void CommandLine::consolePrint(const QString &line)
{
    mLog.append(line + '\n');

    mWriter.erasePrefix();
    mWriter.writeLine(line);

    if (!mIsRunningCommand && !mHasRequestedQuit)
        mWriter.writePrefix();
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
        const QString message = QStringLiteral("Backing up %1...").arg(server);

        consolePrint(message);
    }
}

void CommandLine::backupFinished(QString server)
{
    if (mMode == Standard) {
        const QString message = QStringLiteral("Finished backing up %1").arg(server);

        consolePrint(message);
    }
}

void CommandLine::backupError(QString server, QString errorString)
{
    if (mMode == Standard) {
        const QString message =
                QStringLiteral("Error while backing up %1: %2").arg(server).arg(errorString);

        consolePrint(message);
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

        const QString message = QStringLiteral("Server %1 has started!").arg(serverName);

        consolePrint(message);
    }
}

void CommandLine::serverStopped(bool expected)
{
    if (mMode == Standard) {
        const QString serverName = mServer->getName();

        const QString messageEnd = expected ? QStringLiteral("!") : QStringLiteral(" unexpectedly!");
        const QString message = QStringLiteral("Server %1 has stopped%2").arg(serverName).arg(messageEnd);

        consolePrint(message);
    } else {
        setMode(Standard);
        consolePrint(getError(ConsoleClosed));
    }
}

void CommandLine::serverError(QString errorString)
{
    if (mMode == Standard) {
        const QString serverName = mServer->getName();

        const QString message =
                QStringLiteral("Server %1 has encountered an error: %2").arg(serverName).arg(errorString);

        consolePrint(message);
    }
}

void CommandLine::newLogData(int startingPos)
{
    if (mMode == Console) {
        const QString data = mAddon->readLogFromPos(startingPos);
        consolePrint(data);
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
        return QStringLiteral("Cannot print players for the server: MCSCP is disabled");
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
    case McscpNotYetConnected:
        return QStringLiteral("Mcscp is not yet connected");
    case CannotPrintPlayerInfo:
        return QStringLiteral("Cannot print player info: MCSCP is disabled");
    case PlayerNotFound:
        return QStringLiteral("The specified player is invalid. Note that player names are case-sensitive");
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

        if (!mAddon->isConnected()) {
            mWriter.writeLine(getError(McscpNotYetConnected));
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
    else if (type == QStringLiteral("INFO"))
        infoCommand(parameters);
    else if (type == QStringLiteral("HELP"))
        helpCommand(parameters);
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

        if(!mAddon) {
            mWriter.writeLine(getError(CannotPrintPlayers));
            return;
        }

        if (!mAddon->isConnected()) {
            mWriter.writeLine(getError(McscpNotYetConnected));
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
            mWriter.writeLine(getError(CannotPrintLog));
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

void CommandLine::infoCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        if (!mServer) {
            mWriter.writeLine(getError(NoCurrentServer));
            return;
        }

        const QString running = mServer->isRunning() ? QStringLiteral("Running") : QStringLiteral("Not Running");

        QString info;

        info += QStringLiteral("Current Server: %1\n").arg(mServer->getName());
        info += QStringLiteral("State: %1\n").arg(running);

        if (mAddon && mAddon->isConnected()) {
            const Mcscp::IMcscpServerTable *table = mAddon->getServerTable();
            info += QStringLiteral("Online Players: %1/%2\n").arg(table->getPlayerCount()).arg(table->getMaxPlayers());
            info += QStringLiteral("Tps: %1\n").arg(table->getTps());
            info += QStringLiteral("Max Ram: %1\n").arg(table->getMaxRam());
            info += QStringLiteral("Total Ram: %1\n").arg(table->getTotalRam());
            info += QStringLiteral("Used Ram: %1").arg(table->getUsedRam());
        }

        mWriter.writeLine(info);
    } else {
        if (!mAddon) {
            mWriter.writeLine(getError(CannotPrintPlayerInfo));
            return;
        }

        if (!mAddon->isConnected()) {
            mWriter.writeLine(getError(McscpNotYetConnected));
            return;
        }

        const QString playerName = parameters.first();

        const QStringList uuids = mAddon->getPlayerUuids();

        const Mcscp::IMcscpPlayerTable *playerTable = nullptr;

        for (const QString &uuid : uuids) {
            const Mcscp::IMcscpPlayerTable *table = mAddon->getPlayerTable(uuid);
            if (table->getName() == playerName) {
                playerTable = table;
                break;
            }
        }

        if (!playerTable) {
            mWriter.writeLine(getError(PlayerNotFound));
            return;
        }

        QString playerInfo;

        playerInfo += QStringLiteral("Display Name: %1\n").arg(playerTable->getDisplayName());
        playerInfo += QStringLiteral("IP Address: %1\n").arg(playerTable->getIpAddress());
        playerInfo += QStringLiteral("Max Health: %1\n").arg(playerTable->getMaxHealth());
        playerInfo += QStringLiteral("Health: %1\n").arg(playerTable->getHealth());
        playerInfo += QStringLiteral("Hunger: %1\n").arg(playerTable->getHunger());
        playerInfo += QStringLiteral("Level: %1\n").arg(playerTable->getLevel());
        playerInfo += QStringLiteral("World: %1").arg(playerTable->getWorld());

        mWriter.writeLine(playerInfo);
    }
}

void CommandLine::helpCommand(const QStringList &parameters)
{
    if (parameters.isEmpty()) {
        mWriter.writeLine(
                    QStringLiteral("Syntax:\n"
                                   "Brackets [] indicate an optional parameter which may be automatically filled\n"
                                   "in if certain conditions are met (Ex. There is a current server).\n\n"
                                   "Greater than and less than symbols <> indicate that a parameter is required\n"
                                   "under all conditions\n\n"
                                   "Available commands:\n"
                                   "help [command] - Provideds command-specific help\n"
                                   "list servers - Prints a list of available servers\n"
                                   "list players - Prints a list of online players on the running server\n"
                                   "list addons [server_name] - Prints the list of enabled addons for a server\n"
                                   "start [server_name] - Starts a server. Note: This will stop the running server\n"
                                   "stop - Stops the current running server\n"
                                   "restart - Restarts the current running server\n"
                                   "backup run [server_name] - Runs a backup for the specified server\n"
                                   "backup view [server_name] - Lists all backup files for the specified server\n"
                                   "print serverLog - Prints the entire log from the current server\n"
                                   "print appLog - Prints the entire log from the console\n"
                                   "info - Prints information about the current server\n"
                                   "info [player_name] - Prints information about a specific player on the server"));
    } else {
        const QString commandName = parameters.first().toUpper();

        if (commandName == QStringLiteral("HELP")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "help [command_name]\n\n"
                                       "Description:\n"
                                       "If a command name is specified, the command will print the command-specific\n"
                                       "help page for that command. If a command name is not specified, the command\n"
                                       "will print general help for all commands"));
        } else if (commandName == QStringLiteral("LIST")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "list <param 1> [param 2]\n\n"
                                       "First parameter options:\n"
                                       "Servers - Prints a list of the available servers\n"
                                       "Players - Prints a list of players if there is a current server with MCSCP\n"
                                       "enable and connected\n"
                                       "Addons - Prints a list of addons for the specified server. Uses the current\n"
                                       "server if there is no second parameter, otherwise, the second paramater is\n"
                                       "used\n\n"
                                       "Second Parameter options:\n"
                                       "The second parameter is used to specify a server name when the \"Addons\"\n"
                                       "option is used for the first parameter\n\n"
                                       "Description:\n"
                                       "Prints a list of servers, players, or addons"));
        } else if (commandName == QStringLiteral("START")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "start [server_name]\n\n"
                                       "First parameter options:\n"
                                       "The first parameter is used to specify the name of the server to start.\n\n"
                                       "Description:\n"
                                       "Starts the specified server. Uses the current server if there is no first\n"
                                       "parameter"));
        } else if (commandName == QStringLiteral("STOP")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "stop\n\n"
                                       "Description:\n"
                                       "Stops the current running server."));
        } else if (commandName == QStringLiteral("RESTART")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "restart\n\n"
                                       "Description:\n"
                                       "Restarts the current running server."));
        } else if (commandName == QStringLiteral("BACKUP")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "backup <param 1> [param 2]\n\n"
                                       "First parameter options:\n"
                                       "Run - Run a backup on a server\n"
                                       "View - View backups for a server\n\n"
                                       "Second parameter options:\n"
                                       "The second parameter is used to specify the name of the server that will\n"
                                       "be operated upon. If no second parameter is specified, the current server\n"
                                       "will be used.\n\n"
                                       "Description:\n"
                                       "Runs a backup on a server OR prints a list of all backups for a server"));
        } else if (commandName == QStringLiteral("PRINT")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "print <param 1>\n\n"
                                       "First parameter options:\n"
                                       "ServerLog - Prints the current server's log\n"
                                       "AppLog - Prints the application log\n\n"
                                       "Description:\n"
                                       "Prints the server log if the server has the MCSCP addon OR prints the\n"
                                       "application log"));
        } else if (commandName == QStringLiteral("INFO")) {
            mWriter.writeLine(
                        QStringLiteral("Syntax:\n"
                                       "info [param 1]\n\n"
                                       "First parameter options:\n"
                                       "The first parameter is used to specify a player username in order to print\n"
                                       "information about a specific player instead of about the server\n\n"
                                       "Description:\n"
                                       "Prints information about a specific player if a player is specified, otherwise,\n"
                                       "prints information about the server."));
        } else {
            mWriter.writeLine(getError(InvalidCommand));
        }
    }
}

void CommandLine::processConsoleCommand(const QString &command)
{
    if (mAddon->isConnected())
        mAddon->sendToConsole(command);
}
