#ifndef IMCSCPCLIENTCONFIG_H
#define IMCSCPCLIENTCONFIG_H

#include <QString>

class IMcscpClientConfig
{
public:
    virtual ~IMcscpClientConfig() {}
    virtual bool enabled() const = 0;
    virtual QString address() const = 0;
    virtual int port() const = 0;
};

#endif // IMCSCPCLIENTCONFIG_H
