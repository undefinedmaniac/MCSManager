#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "mcsmanager/core/interfaces/imcsmanagercore.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpservertable.h"
#include "commandlinereader.h"
#include "commandlinewriter.h"

#include <QObject>
#include <QStringList>
#include <QStringListIterator>
#include <QDebug>
#include <QCoreApplication>

namespace Cli { class CommandLine; }

class Cli::CommandLine : public QObject
{
    Q_OBJECT
public:
    CommandLine(QObject *parent = nullptr);

    void start(Core::IMcsManagerCore *core);

private slots:
    void newCommand(QString processCommand);

    void backupStarted(QString server);
    void backupFinished(QString server);
    void backupError(QString server, QString errorString);

    void currentServerChanged();
    void serverStarted();
    void serverStopped(bool expected);
    void serverError(QString errorString);

    void newLogData(int startingPos);

private:
    enum Mode {
        Standard, Console
    };

    enum ErrorType {
        ConsoleClosed, InvalidMode, ConsoleModeUnavailable, InvalidCommand,
        ListItemNotSpecified, NoServersFound, ServerInvalid, NoCurrentServer,
        NoAddonsFound, CannotPrintPlayers, NoPlayersOnline, NoServerSpecified,
        ServerNotRunning
    };

    Mode mMode;
    bool mIsRunningCommand = false;

    Core::IMcsManagerCore *mCore;
    Cli::CommandLineReader mReader;
    Cli::CommandLineWriter mWriter;

    Server::IMcServer *mServer = nullptr;
    Mcscp::IMcscpAddon *mAddon = nullptr;

    void setMode(Mode mode);

    QString getPrefix() const;
    static QString getError(ErrorType type);

    void processCommand(const QString &command);
    void changeMode(const QStringList &parameters);

    void processStandardCommand(const QString &type, const QStringList &parameters);
    void listCommand(const QStringList &parameters);
    void startCommand(const QStringList &parameters);
    void stopCommand();
    void restartCommand();

    void processConsoleCommand(const QString &command);

    void interruptPrint(const QString &line);
};

#endif // COMMANDLINE_H
