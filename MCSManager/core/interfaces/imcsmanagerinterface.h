#ifndef IMCSMANAGERINTERFACE_H
#define IMCSMANAGERINTERFACE_H

class QString;
class QStringList;
class IServerConfig;

class IMcsManagerInterface
{
public:
    virtual ~IMcsManagerInterface() {}

    virtual QStringList serverList() const = 0;
    virtual QStringList backupList(const QString &serverName) const = 0;

    virtual const IServerConfig *getServerConfig(const QString &serverName) const = 0;

    virtual void startServer(const QString &serverName) = 0;
    virtual void runBackup(const QString &serverName) = 0;
};

#endif // IMCSMANAGERINTERFACE_H
