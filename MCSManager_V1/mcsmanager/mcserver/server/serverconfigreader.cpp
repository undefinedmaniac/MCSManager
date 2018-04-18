#include "serverconfigreader.h"

const QRegularExpression ServerConfigReader::ARGUMENT_MATCHER(QStringLiteral(".+?\\s+|.+?$"));

const QString ServerConfigReader::JAVA_PATH_KEY = QStringLiteral("javaPath"),
              ServerConfigReader::JAR_NAME_KEY = QStringLiteral("jarName"),
              ServerConfigReader::WORKING_DIRECTORY_KEY = QStringLiteral("workingDirectory"),
              ServerConfigReader::ARGUMENTS_KEY = QStringLiteral("arguments"),
              ServerConfigReader::REAL_SERVER_KEY = QStringLiteral("isRealServer"),
              ServerConfigReader::UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("unexpectedShutdownBehavior"),
              ServerConfigReader::ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServer");

ServerConfigReader::ServerConfigReader(IConfigFile *config) : mConfig(config)
{
}

QString ServerConfigReader::javaPath() const
{
    const QString data = mConfig->readString(JAVA_PATH_KEY);

    if (data.isEmpty())
        return QStandardPaths::findExecutable(QStringLiteral("java"));

    return data;
}

QString ServerConfigReader::jarName() const
{
    return mConfig->readString(JAR_NAME_KEY);
}

QString ServerConfigReader::workingDirectory() const
{
    return mConfig->readString(WORKING_DIRECTORY_KEY);
}

QStringList ServerConfigReader::arguments() const
{
    const QString subject = mConfig->readString(ARGUMENTS_KEY);
    QRegularExpressionMatchIterator iterator = ARGUMENT_MATCHER.globalMatch(subject);
    QStringList list;

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        const QString string = match.captured();
        list.append(string.trimmed());
    }

    return list;
}

bool ServerConfigReader::isRealServer() const
{
    return mConfig->readBool(REAL_SERVER_KEY);
}

ConfigGlobal::ShutdownBehavior ServerConfigReader::unexpectedShutdownBehavior() const
{
    return convertToShutdownBehavior(mConfig->readString(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY));
}

QString ServerConfigReader::alternativeServer() const
{
    return mConfig->readString(ALTERNATIVE_SERVER_KEY);
}

ConfigGlobal::ConfigData ServerConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(REAL_SERVER_KEY, QStringLiteral("true")));
    data.append(qMakePair(JAVA_PATH_KEY, QStringLiteral("")));
    data.append(qMakePair(JAR_NAME_KEY, QStringLiteral("")));
    data.append(qMakePair(WORKING_DIRECTORY_KEY, QStringLiteral("")));
    data.append(qMakePair(ARGUMENTS_KEY, QStringLiteral("")));
    data.append(qMakePair(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY, QStringLiteral("Restart")));
    data.append(qMakePair(ALTERNATIVE_SERVER_KEY, QStringLiteral("")));
    return data;
}
