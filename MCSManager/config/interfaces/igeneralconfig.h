#ifndef IGENERALCONFIG_H
#define IGENERALCONFIG_H

#include <QString>

class IGeneralConfig
{
public:
    virtual ~IGeneralConfig() {}

    virtual QString defaultServer() const = 0;
};

#endif // IGENERALCONFIG_H
