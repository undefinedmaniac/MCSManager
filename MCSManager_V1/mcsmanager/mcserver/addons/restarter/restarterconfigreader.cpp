#include "restarterconfigreader.h"

using Restarter::RestarterConfigReader;

RestarterConfigReader::RestarterConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

float RestarterConfigReader::period() const
{
    return mConfig->readDouble(Restarter::PERIOD_KEY);
}
