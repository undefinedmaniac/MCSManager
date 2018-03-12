#ifndef IMCSCPADDONCONFIG_H
#define IMCSCPADDONCONFIG_H

class IMcscpAddonConfig
{
public:
    virtual bool mcscpEnabled() const = 0;
    virtual QString mcscpAddress() const = 0;
    virtual int mcscpPort() const = 0;
};

#endif // IMCSCPADDONCONFIG_H
