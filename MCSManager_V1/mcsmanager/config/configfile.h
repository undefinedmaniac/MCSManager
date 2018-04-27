#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "interfaces/iconfigfile.h"
#include "configfunctions.h"

#include <QSettings>

namespace Config { class ConfigFile; }

class Config::ConfigFile : public Config::IConfigFile
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

    void applyDefaults(const Config::ConfigData &defaults) override;

private:
    QSettings mSettings;
};

#endif // CONFIGFILE_H
