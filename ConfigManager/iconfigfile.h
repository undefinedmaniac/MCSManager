#ifndef ICONFIGFILE_H
#define ICONFIGFILE_H

#include "configglobal.h"

class QString;

class IConfigFile
{
public:
    virtual ~IConfigFile() {}

    virtual void setGroup(const QString &group) = 0;

    virtual QString readString(const QString &key) const = 0;
    virtual bool readBool(const QString &key) const = 0;
    virtual double readDouble(const QString &key) const = 0;

    virtual void writeString(const QString &key, const QString &value) = 0;
    virtual void writeBool(const QString &key, bool value) = 0;
    virtual void writeDouble(const QString &key, double value) = 0;

    virtual void applyDefaults(const ConfigData &defaults) = 0;
};

#endif // ICONFIGFILE_H
