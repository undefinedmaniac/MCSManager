#include "configbase.h"

ConfigBase::ConfigBase(const QString &filePath) :
    mSettings(filePath, QSettings::IniFormat)
{
}

QSettings &ConfigBase::getSettings()
{
    return mSettings;
}

const QSettings &ConfigBase::getSettings() const
{
    return mSettings;
}

QVariant ConfigBase::readKey(const QString &base, const QString &key) const
{
    return mSettings.value(base + QStringLiteral("/") + key);
}

void ConfigBase::writeKey(const QString &base, const QString &key, const QVariant &data)
{
    mSettings.setValue(base + QStringLiteral("/") + key, data);
}

int ConfigBase::convertToInt(const QVariant &data)
{
    bool success = false;

    int result = data.toInt(&success);

    if (success)
        return result;

    return -1;
}

bool ConfigBase::convertToBool(const QVariant &data)
{
    const QString string = simplifyString(data.toString());

    return (string == QStringLiteral("TRUE") || string == QStringLiteral("1"));
}

QString ConfigBase::simplifyString(const QString &string)
{
    return string.toUpper().replace(" ", "");
}
