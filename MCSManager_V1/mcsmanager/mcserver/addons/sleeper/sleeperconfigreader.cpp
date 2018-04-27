#include "sleeperconfigreader.h"

using Sleeper::SleeperConfigReader;

SleeperConfigReader::SleeperConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

QString SleeperConfigReader::alternativeServer() const
{
    return mConfig->readString(Sleeper::ALTERNATIVE_SERVER_KEY);
}

float SleeperConfigReader::period() const
{
    return mConfig->readDouble(Sleeper::PERIOD_KEY);
}

Config::ShutdownBehavior SleeperConfigReader::shutdownBehavior() const
{
    return convertToShutdownBehavior(mConfig->readString(Sleeper::SHUTDOWN_BEHAVIOR_KEY));
}
