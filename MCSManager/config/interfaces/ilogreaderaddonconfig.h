#ifndef ILOGREADERADDONCONFIG_H
#define ILOGREADERADDONCONFIG_H

#include <QString>

class ILogReaderAddonConfig
{

public:
    virtual ~ILogReaderAddonConfig() {}

    virtual bool logReaderEnabled() const = 0;
};

#endif // ILOGREADERADDONCONFIG_H
