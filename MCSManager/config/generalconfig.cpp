#include "generalconfig.h"

const QString GeneralConfig::GENERAL_CONFIG_BASE = QStringLiteral("general"),
              GeneralConfig::DEFAULT_SERVER_KEY = QStringLiteral("defaultServer");

GeneralConfig::GeneralConfig(const QString &filePath) : ConfigBase(filePath)
{
    if (getSettings().allKeys().count() <= 0) {
        qDebug() << "Error: No data found inside config file " + filePath;
        generateConfigFile();
    }
}

QString GeneralConfig::defaultServer() const
{
    return readGeneralKey(DEFAULT_SERVER_KEY).toString();
}

void GeneralConfig::generateConfigFile()
{
    qDebug() << "Generating empty config file";

    writeGeneralKey(DEFAULT_SERVER_KEY);

    getSettings().sync();
}

QVariant GeneralConfig::readGeneralKey(const QString &key) const
{
    return readKey(GENERAL_CONFIG_BASE, key);
}

void GeneralConfig::writeGeneralKey(const QString &key, const QVariant &data)
{
    writeKey(GENERAL_CONFIG_BASE, key, data);
}
