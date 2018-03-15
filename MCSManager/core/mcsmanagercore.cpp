#include "mcsmanagercore.h"

McsManagerCore::McsManagerCore()
{

}

void McsManagerCore::startApplication()
{

}

QStringList McsManagerCore::serverList() const
{

}

QStringList McsManagerCore::backupList(const QString &serverName) const
{

}

IServerConfig *McsManagerCore::getServerConfig(const QString &serverName) const
{

}

void McsManagerCore::startServer(const QString &serverName)
{

}

void McsManagerCore::runBackup(const QString &serverName)
{

}

QString McsManagerCore::name() const
{

}

const IServerConfig *McsManagerCore::config() const
{

}

void McsManagerCore::sendChatMsg(const QString &playerName, const QByteArray &message)
{

}

void McsManagerCore::sendMcscpCmd(IMcscpCommand *cmd)
{

}

void McsManagerCore::stop()
{

}

void McsManagerCore::forceStop()
{

}

void McsManagerCore::restart()
{

}

void McsManagerCore::forceRestart()
{

}

QByteArray McsManagerCore::readAllLogData() const
{

}

QByteArray McsManagerCore::readNewLogData()
{

}
