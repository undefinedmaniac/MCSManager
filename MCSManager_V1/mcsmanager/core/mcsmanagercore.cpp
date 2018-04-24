#include "mcsmanagercore.h"

McsManagerCore::McsManagerCore()
{

}

IMcServer *McsManagerCore::getCurrentServer()
{
}

void McsManagerCore::startServer(const QString &serverName)
{
}

QStringList McsManagerCore::getServerList()
{
}

IServerConfig *McsManagerCore::getServerConfig()
{
}

IBackupProcess *McsManagerCore::getBackupProcess()
{
}

BackupList McsManagerCore::getBackupList(const QString &serverName)
{
}

IConfigManager *McsManagerCore::getConfigManager()
{
}

IBackupManager *McsManagerCore::getBackupManager()
{
}

IMcServerBuilder *McsManagerCore::getServerBuilder()
{
}
