#include "mcscpglobal.h"

Config::ConfigData Mcscp::getDefaults()
{
    Config::ConfigData data;
    data.append(qMakePair(ADDRESS_KEY, QStringLiteral("127.0.0.1")));
    data.append(qMakePair(PORT_KEY, QStringLiteral("54620")));;
    return data;
}
