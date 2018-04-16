#ifndef SERVERCONFIGREADER_H
#define SERVERCONFIGREADER_H

#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QStandardPaths>
#include <QRegularExpression>

class ServerConfigReader
{
public:
    enum ShutdownBehavior {
        DoNothing, Restart, StartAltServer
    };

    ServerConfigReader(IConfigFile *config);

    QString javaPath() const;
    QString jarName() const;
    QString workingDirectory() const;
    QStringList arguments() const;
    bool isRealServer() const;
    ShutdownBehavior unexpectedShutdownBehavior() const;
    QString alternativeServer() const;

    static ConfigData getDefaults();

    static const QString JAVA_PATH_KEY,
                         JAR_NAME_KEY,
                         WORKING_DIRECTORY_KEY,
                         ARGUMENTS_KEY,
                         REAL_SERVER_KEY,
                         UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY,
                         ALTERNATIVE_SERVER_KEY;
private:
    IConfigFile *mConfig;

    //ServerConfigReader constants
    static const QRegularExpression ARGUMENT_MATCHER;
};

#endif // SERVERCONFIGREADER_H
