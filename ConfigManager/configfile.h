#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "configfunctions.h"
#include "iconfigfile.h"

#include <QSettings>

class ConfigFile : public IConfigFile
{
public:
    ConfigFile(const QString &filePath);

    // IConfigFile interface
    void setGroup(const QString &group) override;

    QString readString(const QString &key) const override;
    bool readBool(const QString &key) const override;
    double readDouble(const QString &key) const override;

    void writeString(const QString &key, const QString &value) override;
    void writeBool(const QString &key, bool value) override;
    void writeDouble(const QString &key, double value) override;

    void applyDefaults(const ConfigData &defaults) override;

private:
    QSettings mSettings;
};

#endif // CONFIGFILE_H
