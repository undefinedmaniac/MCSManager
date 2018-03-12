#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QString>
#include <QSettings>
#include <QDebug>
#include <QRegularExpression>

#include "./interfaces/iserverconfig.h"

class ServerConfig : public IServerConfig
{
public:
    ServerConfig(const QString &filePath);

    // IServerConfig interface
    QString name() const override;
    QString javaPath() const override;
    QString jarPath() const override;
    QString workingDirectory() const override;
    QStringList arguments() const override;
    QStringList enabledAddons() const override;

    // IServerManagerConfig interface
    ShutdownBehavior unexpectedShutdownBehavior() const override;
    QString alternativeServerName() const override;

    // ILogReaderAddonConfig interface
    bool logReaderEnabled() const override;

    // IServerBackupConfig interface
    int maxBackups() const override;
    QString backupDestination() const override;
    QStringList backupLocations() const override;

    // IBackupAddonConfig interface
    bool backupEnabled() const override;
    bool backupOnServerStart() const override;
    int backupPeriod() const override;

    // ISleeperAddonConfig interface
    bool sleeperEnabled() const override;
    int sleeperPeriod() const override;

    // IRestarterAddonConfig interface
    bool restarterEnabled() const override;
    int restarterPeriod() const override;

    // IMcscpAddonConfig interface
    bool mcscpEnabled() const override;
    QString mcscpAddress() const override;
    int mcscpPort() const override;

protected:
    virtual QStringList getEnabledAddons() const;

private:
    QSettings mSettings;
    QStringList mArguments, mEnabledAddons, mBackupLocations;

    void generateConfigFile();

    QStringList getArguments() const;
    QStringList getBackupLocations() const;

    QVariant readKey(const QString &base, const QString &key) const;
    QVariant readGeneralKey(const QString &key) const;
    QVariant readBackupKey(const QString &key) const;
    QVariant readSleeperKey(const QString &key) const;
    QVariant readRestarterKey(const QString &key) const;
    QVariant readMcscpKey(const QString &key) const;

    void writeKey(const QString &base, const QString &key, const QVariant &data = QVariant(""));
    void writeGeneralKey(const QString &key, const QVariant &data = QVariant(""));
    void writeBackupKey(const QString &key, const QVariant &data = QVariant(""));
    void writeSleeperKey(const QString &key, const QVariant &data = QVariant(""));
    void writeRestarterKey(const QString &key, const QVariant &data = QVariant(""));
    void writeMcscpKey(const QString &key, const QVariant &data = QVariant(""));

    static int convertToInt(const QVariant &data);
    static bool convertToBool(const QVariant &data);

    static QString simplifyString(const QString &string);

    //ServerConfig Constants
    static const QString SERVER_CONFIG_BASE,
                         SERVER_NAME,
                         JAVA_PATH_KEY,
                         JAR_PATH_KEY,
                         WORKING_DIRECTORY_KEY,
                         ARGUMENTS_KEY,
                         UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY,
                         ALTERNATIVE_SERVER_KEY,
                         LOG_NAME,
                         LOG_ENABLED_KEY,
                         BACKUP_NAME,
                         BACKUP_CONFIG_BASE,
                         MAX_BACKUPS_KEY,
                         BACKUP_DESTINATION_KEY,
                         BACKUP_LOCATION_KEY,
                         BACKUP_ENABLED_KEY,
                         BACKUP_ON_SERVER_START_KEY,
                         BACKUP_PERIOD_KEY,
                         SLEEPER_NAME,
                         SLEEPER_CONFIG_BASE,
                         SLEEPER_ENABLED_KEY,
                         SLEEPER_PERIOD_KEY,
                         RESTARTER_NAME,
                         RESTARTER_CONFIG_BASE,
                         RESTARTER_ENABLED_KEY,
                         RESTARTER_PERIOD_KEY,
                         MCSCP_NAME,
                         MCSCP_CONFIG_BASE,
                         MCSCP_ENABLED_KEY,
                         MCSCP_ADDRESS_KEY,
                         MCSCP_PORT_KEY;
};

#endif // SERVERCONFIG_H
