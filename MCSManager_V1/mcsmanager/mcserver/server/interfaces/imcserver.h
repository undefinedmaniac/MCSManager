#ifndef IMCSERVER_H
#define IMCSERVER_H

class QString;
class QStringList;
namespace Server { class IMcServerBuilder; }
namespace Core { class IMcsManagerCore; }
namespace Backup { class IBackupManager; }

namespace Config
{
    class IServerConfig;
    class IConfigManager;
}

namespace Addon
{
    class McServerAddonBase;
    class IMcServerAddon;
}

#include <QObject>

namespace Server { class IMcServer; }

class Server::IMcServer : public QObject
{
    Q_OBJECT
public:
    friend class Addon::McServerAddonBase;

    IMcServer(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IMcServer() {}

    virtual QString getName() const = 0;
    virtual Config::IServerConfig *getConfig() = 0;

    virtual void addAddon(Addon::IMcServerAddon *addon) = 0;
    virtual void removeAddon(const QString &addonName) = 0;
    virtual Addon::IMcServerAddon *getAddon(const QString &addonName) = 0;
    virtual QStringList getAddonList() const = 0;

    virtual void start() = 0;
    virtual void restart() = 0;
    virtual void stop() = 0;

    virtual bool isRunning() const = 0;

signals:
    void started();
    void stopped(bool expected);
    void error(QString errorMessage);

protected:
    virtual Core::IMcsManagerCore *getCore() = 0;
    virtual Config::IConfigManager *getConfigManager() = 0;
    virtual Backup::IBackupManager *getBackupManager() = 0;
    virtual Server::IMcServerBuilder *getServerBuilder() = 0;
};

#endif // IMCSERVER_H
