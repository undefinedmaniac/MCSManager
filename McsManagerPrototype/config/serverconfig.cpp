#include "serverconfig.h"

ServerConfig::ServerConfig(const QString &filePath) : mSettings(filePath, QSettings::IniFormat)
{

}

ServerConfig::~ServerConfig()
{

}

QString ServerConfig::javaPath() const
{
    return mSettings.value(JAVA_PATH_KEY);
}

QString ServerConfig::jarPath() const
{
    return mSettings.value(JAR_PATH_KEY);
}

QString ServerConfig::workingDirectory() const
{
    return mSettings.value(WORKING_DIRECTORY_KEY);
}

QStringList ServerConfig::arguments() const
{
    return mSettings.value(ARGUMENTS_KEY).toStringList();
}

int ServerConfig::unexpectedShutdownBehavior() const
{
    return mSettings.value(UNEXPECTED_SHUTDOWN_BEHAVIOR_KEY).toInt();
}

IBackupServiceConfig *ServerConfig::backupServiceConfig() const
{

}

IMcscpClientConfig *ServerConfig::mcscpClientConfig() const
{

}

IServerSleeperConfig *ServerConfig::serverSleeperConfig() const
{

}

IRestarterConfig *ServerConfig::restarterConfig() const
{

}
