#ifndef ILOGREADERADDONCONFIG_H
#define ILOGREADERADDONCONFIG_H

class ILogReaderAddonConfig
{

public:
    virtual ~ILogReaderAddonConfig() {}

    virtual bool logReaderEnabled() const = 0;
};

#endif // ILOGREADERADDONCONFIG_H
