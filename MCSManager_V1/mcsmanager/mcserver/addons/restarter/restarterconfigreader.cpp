#include "restarterconfigreader.h"

const QString RestarterConfigReader::PERIOD_KEY = QStringLiteral("period"),
              RestarterConfigReader::SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("shutdownBehavior"),
              RestarterConfigReader::ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServer");

RestarterConfigReader::RestarterConfigReader(IConfigFile *config) : mConfig(config)
{
}

QString RestarterConfigReader::alternativeServer() const
{
    return mConfig->readString(ALTERNATIVE_SERVER_KEY);
}

int RestarterConfigReader::period() const
{
    return mConfig->readDouble(PERIOD_KEY);
}

ConfigGlobal::ShutdownBehavior RestarterConfigReader::shutdownBehavior() const
{
    return convertToShutdownBehavior(mConfig->readString(SHUTDOWN_BEHAVIOR_KEY));
}

ConfigGlobal::ConfigData RestarterConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("")));
    data.append(qMakePair(SHUTDOWN_BEHAVIOR_KEY, QStringLiteral("DoNothing")));
    data.append(qMakePair(ALTERNATIVE_SERVER_KEY, QStringLiteral("")));
    return data;
}
