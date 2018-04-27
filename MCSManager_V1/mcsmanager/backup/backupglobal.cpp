#include "backupglobal.h"

Config::ConfigData Backup::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(SOURCES_KEY, QStringLiteral("")));
    data.append(qMakePair(DESTINATION_KEY, QStringLiteral("")));
    return data;
}
