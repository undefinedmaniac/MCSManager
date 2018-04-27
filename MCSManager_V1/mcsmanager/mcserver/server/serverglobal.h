#ifndef SERVERGLOBAL_H
#define SERVERGLOBAL_H

#include "mcsmanager/config/configglobal.h"

#include <QString>

namespace Server
{

const QString JAVA_PATH_KEY = QStringLiteral("javaPath"),
              JAR_NAME_KEY = QStringLiteral("jarName"),
              WORKING_DIRECTORY_KEY = QStringLiteral("workingDirectory"),
              BEFORE_ARGUMENTS_KEY = QStringLiteral("beforeArguments"),
              AFTER_ARGUMENTS_KEY = QStringLiteral("afterArguments"),
              REAL_SERVER_KEY = QStringLiteral("isRealServer"),
              UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("unexpectedShutdownBehavior"),
              ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServer");

Config::ConfigData getDefaults();

}

#endif // SERVERGLOBAL_H
