#ifndef IMCSMANAGERCORE_H
#define IMCSMANAGERCORE_H

class QString;
class QStringList;
namespace Server { class IMcServerBuilder; }

namespace Config
{
    class IServerConfig;
    class IConfigManager;
}

namespace Backup
{
    class IBackupProcess;
    class IBackupManager;
}

namespace Server { class IMcServer; }

#include <QObject>

namespace Core { class IMcsManagerCore; }

class Core::IMcsManagerCore : public QObject
{
    Q_OBJECT
public:
    friend class McsManagerCoreChild;

    virtual ~IMcsManagerCore() {}

    virtual Server::IMcServer *getCurrentServer() = 0;
    virtual void startServer(const QString &serverName) = 0;
    virtual QStringList getServerList() = 0;
    virtual Config::IServerConfig *getServerConfig(const QString &serverName) = 0;
    virtual Backup::IBackupProcess *getBackupProcess(const QString &serverName) = 0;
    virtual QStringList getBackupList(const QString &serverName) = 0;

signals:
    void currentServerChanged();

    void backupStarted(QString server);
    void backupFinished(QString server);
    void backupError(QString server, QString errorString);

protected:
    virtual Config::IConfigManager *getConfigManager() = 0;
    virtual Backup::IBackupManager *getBackupManager() = 0;
    virtual Server::IMcServerBuilder *getServerBuilder() = 0;
};

#endif // IMCSMANAGERCORE_H
