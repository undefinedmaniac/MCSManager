#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "iconfigfile.h"
#include "configfunctions.h"

#include <QSettings>
#include <QHash>
#include <QDebug>

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

    void setDefaultString(const QString &key, const QString &value) override;
    void setDefaultBool(const QString &key, bool value) override;
    void setDefaultDouble(const QString &key, double value) override;

    void applyDefaults() override;

private:
    QSettings mSettings;
    QHash<QString, QVariant> mDefaults;

    static double convertToDouble(const QVariant &data);
    static bool convertToBool(const QVariant &data);
};

#endif // CONFIGFILE_H
