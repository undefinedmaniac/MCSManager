#include "mcscpconfigreader.h"

const QString McscpConfigReader::ADDRESS_KEY = QStringLiteral("address"),
              McscpConfigReader::PORT_KEY = QStringLiteral("port");

McscpConfigReader::McscpConfigReader(IConfigFile *config) : mConfig(config)
{
}

QString McscpConfigReader::address() const
{
    return mConfig->readString(ADDRESS_KEY);
}

int McscpConfigReader::port() const
{
    return mConfig->readDouble(PORT_KEY);
}

ConfigGlobal::ConfigData McscpConfigReader::getDefaults()
{
    ConfigGlobal::ConfigData data;
    data.append(qMakePair(ADDRESS_KEY, QStringLiteral("127.0.0.1")));
    data.append(qMakePair(PORT_KEY, QStringLiteral("25566")));;
    return data;
}
