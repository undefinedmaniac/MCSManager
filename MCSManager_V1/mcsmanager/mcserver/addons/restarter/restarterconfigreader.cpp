#include "restarterconfigreader.h"

const QString RestarterConfigReader::ADDON_NAME = QStringLiteral("restarter"),
              RestarterConfigReader::PERIOD_KEY = QStringLiteral("period");

RestarterConfigReader::RestarterConfigReader(IConfigFile *config) : mConfig(config)
{
}

int RestarterConfigReader::period() const
{
    return mConfig->readDouble(PERIOD_KEY);
}

QString RestarterConfigReader::getAddonName()
{
    return ADDON_NAME;
}

ConfigGlobal::ConfigData RestarterConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(PERIOD_KEY, QStringLiteral("180")));
    return data;
}
