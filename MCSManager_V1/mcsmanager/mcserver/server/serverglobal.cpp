#include "serverglobal.h"

Config::ConfigData Server::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(REAL_SERVER_KEY, QStringLiteral("true")));
    data.append(qMakePair(JAVA_PATH_KEY, QStringLiteral("")));
    data.append(qMakePair(JAR_NAME_KEY, QStringLiteral("")));
    data.append(qMakePair(WORKING_DIRECTORY_KEY, QStringLiteral("")));
    data.append(qMakePair(BEFORE_ARGUMENTS_KEY, QStringLiteral("")));
    data.append(qMakePair(AFTER_ARGUMENTS_KEY, QStringLiteral("")));
    data.append(qMakePair(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY, QStringLiteral("Restart")));
    data.append(qMakePair(ALTERNATIVE_SERVER_KEY, QStringLiteral("")));
    return data;
}
