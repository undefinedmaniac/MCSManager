#include "mcscpconfigreader.h"

using Mcscp::McscpConfigReader;

McscpConfigReader::McscpConfigReader(Config::IConfigFile *config) : mConfig(config)
{
}

QString McscpConfigReader::address() const
{
    return mConfig->readString(Mcscp::ADDRESS_KEY);
}

int McscpConfigReader::port() const
{
    return mConfig->readDouble(Mcscp::PORT_KEY);
}
