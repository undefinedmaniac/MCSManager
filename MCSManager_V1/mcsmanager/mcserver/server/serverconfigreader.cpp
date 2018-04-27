#include "serverconfigreader.h"

using Server::ServerConfigReader;

const QRegularExpression ServerConfigReader::ARGUMENT_MATCHER(QStringLiteral(".+?\\s+|.+?$"));

ServerConfigReader::ServerConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

QString ServerConfigReader::javaPath() const
{
    const QString data = mConfig->readString(Server::JAVA_PATH_KEY);

    if (data.isEmpty())
        return QStandardPaths::findExecutable(QStringLiteral("java"));

    return data;
}

QString ServerConfigReader::jarName() const
{
    return mConfig->readString(Server::JAR_NAME_KEY);
}

QString ServerConfigReader::workingDirectory() const
{
    return mConfig->readString(Server::WORKING_DIRECTORY_KEY);
}

QStringList ServerConfigReader::beforeArguments() const
{
    return argumentHelper(Server::BEFORE_ARGUMENTS_KEY);
}

QStringList ServerConfigReader::afterArguments() const
{
    return argumentHelper(Server::AFTER_ARGUMENTS_KEY);
}

bool ServerConfigReader::isRealServer() const
{
    return mConfig->readBool(Server::REAL_SERVER_KEY);
}

Config::ShutdownBehavior ServerConfigReader::unexpectedShutdownBehavior() const
{
    return convertToShutdownBehavior(mConfig->readString(Server::UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY));
}

QString ServerConfigReader::alternativeServer() const
{
    return mConfig->readString(Server::ALTERNATIVE_SERVER_KEY);
}

QStringList ServerConfigReader::argumentHelper(const QString &key) const
{
    const QString subject = mConfig->readString(key);
    QRegularExpressionMatchIterator iterator = ARGUMENT_MATCHER.globalMatch(subject);
    QStringList list;

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        const QString string = match.captured();
        list.append(string.trimmed());
    }

    return list;
}

