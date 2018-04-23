#include "restarterconfigreader.h"

const QString RestarterConfigReader::PERIOD_KEY = QStringLiteral("period");

RestarterConfigReader::RestarterConfigReader(IConfigFile *config) : mConfig(config)
{
}

int RestarterConfigReader::period() const
{
    return mConfig->readDouble(PERIOD_KEY);
}

ConfigGlobal::ConfigData RestarterConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("180")));
    return data;
}
