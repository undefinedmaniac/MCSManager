#include "configfile.h"

ConfigFile::ConfigFile(const QString &filePath) :
    mSettings(filePath, QSettings::IniFormat)
{
}

void ConfigFile::setGroup(const QString &group)
{
    mSettings.beginGroup(group);
}

QString ConfigFile::readString(const QString &key) const
{
    return mSettings.value(key, QStringLiteral("")).toString();
}

bool ConfigFile::readBool(const QString &key) const
{
    return convertToBool(mSettings.value(key));
}

double ConfigFile::readDouble(const QString &key) const
{
    return convertToDouble(mSettings.value(key));
}

void ConfigFile::writeString(const QString &key, const QString &value)
{
    mSettings.setValue(key, value);
}

void ConfigFile::writeBool(const QString &key, bool value)
{
    QString data;

    if (value)
        data = QStringLiteral("true");
    else
        data = QStringLiteral("false");

    mSettings.setValue(key, data);
}

void ConfigFile::writeDouble(const QString &key, double value)
{
    mSettings.setValue(key, value);
}

void ConfigFile::applyDefaults(const ConfigData &defaults)
{
    for (int i = 0; i < defaults.size(); i++) {
        const QPair<QString, QString> &pair = defaults.at(i);
        if (!mSettings.contains(pair.first))
            mSettings.setValue(pair.first, pair.second);
    }

    mSettings.sync();
}
