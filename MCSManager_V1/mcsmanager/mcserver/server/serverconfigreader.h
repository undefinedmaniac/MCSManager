#ifndef SERVERCONFIGREADER_H
#define SERVERCONFIGREADER_H

#include "serverglobal.h"
#include "mcsmanager/config/interfaces/iconfigfile.h"
#include "mcsmanager/config/configfunctions.h"

#include <QStandardPaths>
#include <QRegularExpression>

namespace Server { class ServerConfigReader; }

class Server::ServerConfigReader
{
public:
    ServerConfigReader(Config::IConfigFile *config);

    QString javaPath() const;
    QString jarName() const;
    QString workingDirectory() const;
    QStringList beforeArguments() const;
    QStringList afterArguments() const;
    bool isRealServer() const;
    Config::ShutdownBehavior unexpectedShutdownBehavior() const;
    QString alternativeServer() const;

private:
    Config::IConfigFile *mConfig;

    //ServerConfigReader constants
    static const QRegularExpression ARGUMENT_MATCHER;

    QStringList argumentHelper(const QString &key) const;
};

#endif // SERVERCONFIGREADER_H
