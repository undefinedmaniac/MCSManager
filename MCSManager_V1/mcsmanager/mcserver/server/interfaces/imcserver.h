#ifndef IMCSERVER_H
#define IMCSERVER_H

class QString;
class IMcServerAddon;
class IServerConfig;
class QStringList;
class IMcsManagerCore;
class IConfigManager;
class IBackupManager;
class IMcServerBuilder;

class IMcServer
{
public:
    friend class McServerAddonBase;

    virtual ~IMcServer() {}

    virtual IServerConfig *getConfig() = 0;

    virtual void addAddon(IMcServerAddon *addon) = 0;
    virtual void removeAddon(const QString &addonName) = 0;
    virtual IMcServerAddon *getAddon(const QString &addonName) = 0;
    virtual QStringList getAddonList() const = 0;

    virtual void start() = 0;
    virtual void restart() = 0;
    virtual void stop() = 0;

    virtual bool isRunning() const = 0;

    virtual void started() = 0;
    virtual void stopped(bool expected) = 0;
    virtual void error(QString errorMessage) = 0;

protected:
    virtual IMcsManagerCore *getCore() = 0;
    virtual IConfigManager *getConfigManager() = 0;
    virtual IBackupManager *getBackupManager() = 0;
    virtual IMcServerBuilder *getServerBuilder() = 0;
};

#endif // IMCSERVER_H
