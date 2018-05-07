#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "mcsmanager/core/interfaces/imcsmanagercore.h"
#include "mcsmanager/mcserver/server/interfaces/imcserver.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/mcserver/addons/interfaces/imcserveraddon.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpservertable.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpplayertable.h"
#include "mcsmanager/backup/interfaces/ibackupprocess.h"
#include "commandlinereader.h"
#include "commandlinewriter.h"

#include <QObject>
#include <QStringList>
#include <QTimer>
#include <QStringBuilder>
#include <QEventLoop>

namespace Cli { class CommandLine; }

class Cli::CommandLine : public QObject
{
    Q_OBJECT
public:
    CommandLine(QObject *parent = nullptr);

    void start(Core::IMcsManagerCore *core);
    void waitForStop();

signals:
    void started();
    void stopped();
    void exitApplication();

public slots:
    void consolePrint(const QString &line);

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
        NoServersFound, ServerInvalid, NoCurrentServer, NoAddonsFound,
        CannotPrintPlayers, NoPlayersOnline, NoServerSpecified, ServerNotRunning,
        ServerAlreadyRunning, NoActionSpecified, NoBackupsFound, InvalidObject,
        InvalidAction, NoObjectSpecified, CannotPrintLog, ServerLogEmpty, AppLogEmpty,
        McscpNotYetConnected, CannotPrintPlayerInfo, PlayerNotFound
    };

    Mode mMode;
    bool mIsRunningCommand = false;
    bool mHasRequestedQuit = false;

    Core::IMcsManagerCore *mCore;
    Cli::CommandLineReader mReader;
    Cli::CommandLineWriter mWriter;

    Server::IMcServer *mServer = nullptr;
    Mcscp::IMcscpAddon *mAddon = nullptr;

    QString mLog;

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
    void backupCommand(const QStringList &parameters);
    void printCommand(const QStringList &parameters);
    void infoCommand(const QStringList &parameters);
    void helpCommand(const QStringList &parameters);

    void processConsoleCommand(const QString &command);
};

#endif // COMMANDLINE_H
