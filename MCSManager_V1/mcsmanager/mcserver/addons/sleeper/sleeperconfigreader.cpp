#include "sleeperconfigreader.h"

const QString SleeperConfigReader::PERIOD_KEY = QStringLiteral("period"),
              SleeperConfigReader::SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("shutdownBehavior"),
              SleeperConfigReader::ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServer");

SleeperConfigReader::SleeperConfigReader(IConfigFile *config) : mConfig(config)
{
}

QString SleeperConfigReader::alternativeServer() const
{
    return mConfig->readString(ALTERNATIVE_SERVER_KEY);
}

int SleeperConfigReader::period() const
{
    return mConfig->readDouble(PERIOD_KEY);
}

ConfigGlobal::ShutdownBehavior SleeperConfigReader::shutdownBehavior() const
{
    return convertToShutdownBehavior(mConfig->readString(SHUTDOWN_BEHAVIOR_KEY));
}

ConfigGlobal::ConfigData SleeperConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("60")));
    data.append(qMakePair(SHUTDOWN_BEHAVIOR_KEY, QStringLiteral("DoNothing")));
    data.append(qMakePair(ALTERNATIVE_SERVER_KEY, QStringLiteral("")));
    return data;
}
