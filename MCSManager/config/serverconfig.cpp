#include "serverconfig.h"

const QString ServerConfig::SERVER_CONFIG_BASE = QStringLiteral("general"),
              ServerConfig::SERVER_NAME = QStringLiteral("name"),
              ServerConfig::JAVA_PATH_KEY = QStringLiteral("javaPath"),
              ServerConfig::JAR_PATH_KEY = QStringLiteral("jarName"),
              ServerConfig::WORKING_DIRECTORY_KEY = QStringLiteral("workingDirectory"),
              ServerConfig::ARGUMENTS_KEY = QStringLiteral("arguments"),
              ServerConfig::UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY = QStringLiteral("unexpectedShutdownBehavior"),
              ServerConfig::ALTERNATIVE_SERVER_KEY = QStringLiteral("alternativeServerKey"),
              ServerConfig::LOG_NAME = QStringLiteral("logReader"),
              ServerConfig::LOG_ENABLED_KEY = QStringLiteral("logEnabled"),
              ServerConfig::BACKUP_NAME = QStringLiteral("backup"),
              ServerConfig::BACKUP_CONFIG_BASE = QStringLiteral("backup"),
              ServerConfig::MAX_BACKUPS_KEY = QStringLiteral("maxBackups"),
              ServerConfig::BACKUP_DESTINATION_KEY = QStringLiteral("destination"),
              ServerConfig::BACKUP_LOCATION_KEY = QStringLiteral("location"),
              ServerConfig::BACKUP_ENABLED_KEY = QStringLiteral("enabled"),
              ServerConfig::BACKUP_ON_SERVER_START_KEY = QStringLiteral("backupOnServerStart"),
              ServerConfig::BACKUP_PERIOD_KEY = QStringLiteral("backupPeriod"),
              ServerConfig::SLEEPER_NAME = QStringLiteral("sleeper"),
              ServerConfig::SLEEPER_CONFIG_BASE = QStringLiteral("sleeper"),
              ServerConfig::SLEEPER_ENABLED_KEY = QStringLiteral("enabled"),
              ServerConfig::SLEEPER_PERIOD_KEY = QStringLiteral("period"),
              ServerConfig::RESTARTER_NAME = QStringLiteral("restarter"),
              ServerConfig::RESTARTER_CONFIG_BASE = QStringLiteral("restarter"),
              ServerConfig::RESTARTER_ENABLED_KEY = QStringLiteral("enabled"),
              ServerConfig::RESTARTER_PERIOD_KEY = QStringLiteral("period"),
              ServerConfig::MCSCP_NAME = QStringLiteral("mcscp"),
              ServerConfig::MCSCP_CONFIG_BASE = QStringLiteral("mcscp"),
              ServerConfig::MCSCP_ENABLED_KEY = QStringLiteral("enabled"),
              ServerConfig::MCSCP_ADDRESS_KEY = QStringLiteral("address"),
              ServerConfig::MCSCP_PORT_KEY = QStringLiteral("port");

ServerConfig::ServerConfig(const QString &filePath) :
    mSettings(filePath, QSettings::IniFormat)
{
    if (mSettings.allKeys().count() <= 0) {
        qDebug() << "Error: No data found inside config file " + filePath;
        generateConfigFile();
    } else {
        mArguments = getArguments();
        mEnabledAddons = getEnabledAddons();
        mBackupLocations = getBackupLocations();
    }
}

QString ServerConfig::name() const
{
    return readGeneralKey(SERVER_NAME).toString();
}

QString ServerConfig::javaPath() const
{
    return readGeneralKey(JAVA_PATH_KEY).toString();
}

QString ServerConfig::jarPath() const
{
    return readGeneralKey(JAR_PATH_KEY).toString();
}

QString ServerConfig::workingDirectory() const
{
    return readGeneralKey(WORKING_DIRECTORY_KEY).toString();
}

QStringList ServerConfig::arguments() const
{
    return mArguments;
}

QStringList ServerConfig::enabledAddons() const
{
    return mEnabledAddons;
}

IServerConfig::ShutdownBehavior ServerConfig::unexpectedShutdownBehavior() const
{
    const QString data = simplifyString(readGeneralKey(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY).toString());

    if (data == QStringLiteral("RESTART"))
        return ServerConfig::RestartServer;
    else if (data == QStringLiteral("STARTALTERNATIVESERVER"))
        return ServerConfig::StartAlternativeServer;

    return ServerConfig::DoNothing;
}

QString ServerConfig::alternativeServerName() const
{
    return readGeneralKey(ALTERNATIVE_SERVER_KEY).toString();
}

bool ServerConfig::logReaderEnabled() const
{
    return convertToBool(readGeneralKey(LOG_ENABLED_KEY));
}

int ServerConfig::maxBackups() const
{   
    return convertToInt(readBackupKey(MAX_BACKUPS_KEY));
}

QString ServerConfig::backupDestination() const
{
    return readBackupKey(BACKUP_DESTINATION_KEY).toString();
}

QStringList ServerConfig::backupLocations() const
{
    return mBackupLocations;
}

bool ServerConfig::backupEnabled() const
{
    return convertToBool(readBackupKey(BACKUP_ENABLED_KEY));
}

bool ServerConfig::backupOnServerStart() const
{
    return convertToBool(readBackupKey(BACKUP_ON_SERVER_START_KEY));
}

int ServerConfig::backupPeriod() const
{
    return convertToInt(readBackupKey(BACKUP_PERIOD_KEY));
}

bool ServerConfig::sleeperEnabled() const
{
    return convertToBool(readSleeperKey(SLEEPER_ENABLED_KEY));
}

int ServerConfig::sleeperPeriod() const
{
    return convertToInt(readSleeperKey(SLEEPER_PERIOD_KEY));
}

bool ServerConfig::restarterEnabled() const
{
    return convertToBool(readRestarterKey(RESTARTER_ENABLED_KEY));
}

int ServerConfig::restarterPeriod() const
{
    return convertToInt(readRestarterKey(RESTARTER_PERIOD_KEY));
}

bool ServerConfig::mcscpEnabled() const
{
    return convertToBool(readMcscpKey(MCSCP_ENABLED_KEY));
}

QString ServerConfig::mcscpAddress() const
{
    return readMcscpKey(MCSCP_ADDRESS_KEY).toString();
}

int ServerConfig::mcscpPort() const
{
    return convertToInt(readMcscpKey(MCSCP_PORT_KEY));
}

QStringList ServerConfig::getEnabledAddons() const
{
    QStringList addons;

    if (logReaderEnabled())
        addons.append(LOG_NAME);
    if (backupEnabled())
        addons.append(BACKUP_NAME);
    if (sleeperEnabled())
        addons.append(SLEEPER_NAME);
    if (restarterEnabled())
        addons.append(RESTARTER_NAME);
    if (mcscpEnabled())
        addons.append(MCSCP_NAME);

    return addons;
}

void ServerConfig::generateConfigFile()
{
    qDebug() << "Generating empty config file";

    writeGeneralKey(SERVER_NAME);
    writeGeneralKey(JAVA_PATH_KEY);
    writeGeneralKey(JAR_PATH_KEY);
    writeGeneralKey(WORKING_DIRECTORY_KEY);
    writeGeneralKey(ARGUMENTS_KEY);
    writeGeneralKey(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY);
    writeGeneralKey(ALTERNATIVE_SERVER_KEY);
    writeGeneralKey(LOG_ENABLED_KEY);

    writeBackupKey(MAX_BACKUPS_KEY);
    writeBackupKey(BACKUP_DESTINATION_KEY);
    writeBackupKey(BACKUP_LOCATION_KEY);
    writeBackupKey(BACKUP_ENABLED_KEY);
    writeBackupKey(BACKUP_ON_SERVER_START_KEY);
    writeBackupKey(BACKUP_PERIOD_KEY);

    writeSleeperKey(SLEEPER_ENABLED_KEY);
    writeSleeperKey(SLEEPER_PERIOD_KEY);

    writeRestarterKey(RESTARTER_ENABLED_KEY);
    writeRestarterKey(RESTARTER_PERIOD_KEY);

    writeMcscpKey(MCSCP_ENABLED_KEY);
    writeMcscpKey(MCSCP_ADDRESS_KEY);
    writeMcscpKey(MCSCP_PORT_KEY);

    mSettings.sync();
}

QStringList ServerConfig::getArguments() const
{
    QRegularExpression matcher(QStringLiteral(".+?\\s+|.+?$"));

    const QString subject = readGeneralKey(ARGUMENTS_KEY).toString();
    QRegularExpressionMatchIterator iterator = matcher.globalMatch(subject);
    QStringList list;

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString string = match.captured();
        list.append(string.replace(QStringLiteral(" "), QStringLiteral("")));
    }

    return list;
}

QStringList ServerConfig::getBackupLocations() const
{
    QRegularExpression matcher(QStringLiteral(" *([^;]+?) *(?:;|$)"));

    const QString subject = readBackupKey(BACKUP_LOCATION_KEY).toString();
    QRegularExpressionMatchIterator iterator = matcher.globalMatch(subject);
    QStringList list;

    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        QString string = match.captured(1);
        if (string != NULL)
            list.append(string);
    }

    return list;
}

QVariant ServerConfig::readGeneralKey(const QString &key) const
{
    return readKey(SERVER_CONFIG_BASE, key);
}

QVariant ServerConfig::readBackupKey(const QString &key) const
{
    return readKey(BACKUP_CONFIG_BASE, key);
}

QVariant ServerConfig::readSleeperKey(const QString &key) const
{
    return readKey(SLEEPER_CONFIG_BASE, key);
}

QVariant ServerConfig::readRestarterKey(const QString &key) const
{
    return readKey(RESTARTER_CONFIG_BASE, key);
}

QVariant ServerConfig::readMcscpKey(const QString &key) const
{
    return readKey(MCSCP_CONFIG_BASE, key);
}

void ServerConfig::writeKey(const QString &base, const QString &key, const QVariant &data)
{
    mSettings.setValue(base + QStringLiteral("/") + key, data);
}

void ServerConfig::writeGeneralKey(const QString &key, const QVariant &data)
{
    writeKey(SERVER_CONFIG_BASE, key, data);
}

void ServerConfig::writeBackupKey(const QString &key, const QVariant &data)
{
    writeKey(BACKUP_CONFIG_BASE, key, data);
}

void ServerConfig::writeSleeperKey(const QString &key, const QVariant &data)
{
    writeKey(SLEEPER_CONFIG_BASE, key, data);
}

void ServerConfig::writeRestarterKey(const QString &key, const QVariant &data)
{
    writeKey(RESTARTER_CONFIG_BASE, key, data);
}

void ServerConfig::writeMcscpKey(const QString &key, const QVariant &data)
{
    writeKey(MCSCP_CONFIG_BASE, key, data);
}

QVariant ServerConfig::readKey(const QString &base, const QString &key) const
{
    return mSettings.value(base + QStringLiteral("/") + key);
}

int ServerConfig::convertToInt(const QVariant &data)
{
    bool success = false;

    int result = data.toInt(&success);

    if (success)
        return result;

    return -1;
}

bool ServerConfig::convertToBool(const QVariant &data)
{
    const QString string = simplifyString(data.toString());

    return (string == QStringLiteral("TRUE") || string == QStringLiteral("1"));
}

QString ServerConfig::simplifyString(const QString &string)
{
    return string.toUpper().replace(" ", "");
}
