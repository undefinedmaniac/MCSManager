#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QSettings>

#include "config/interface/iserverconfig.h"

class ServerConfig : public IServerConfig
{
public:
    ServerConfig(const QString &filePath);
    ~ServerConfig();

    QString javaPath() const;
    QString jarPath() const;
    QString workingDirectory() const;
    QStringList arguments() const;
    int unexpectedShutdownBehavior() const;
    IBackupServiceConfig *backupServiceConfig() const;
    IMcscpClientConfig *mcscpClientConfig() const;
    IServerSleeperConfig *serverSleeperConfig() const;
    IRestarterConfig *restarterConfig() const;

private:
    QSettings mSettings;

    IBackupServiceConfig *mBackupConfig;
    IMcscpClientConfig *mMcscpConfig;
    IServerSleeperConfig *mSleeperConfig;
    IRestarterConfig *mRestarterConfig;

    //CONFIG KEYS
    const QString JAVA_PATH_KEY = "javaPath";
    const QString JAR_PATH_KEY = "jarPath";
    const QString WORKING_DIRECTORY_KEY = "workingDirectory";
    const QString ARGUMENTS_KEY = "arguments";
    const QString UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY = "unexpectedShutdownBehavior";
};

#endif // SERVERCONFIG_H
