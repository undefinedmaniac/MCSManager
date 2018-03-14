#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDir>
#include <QHash>
#include <QString>
#include <QScopedPointer>

#include "serverconfig.h"
#include "generalconfig.h"
#include "configfunctions.h"
#include "config/interfaces/igeneralconfig.h"
#include "config/interfaces/iserverconfig.h"
#include "config/interfaces/iconfigmanager.h"

class ConfigManager : public IConfigManager
{
public:
    ConfigManager();
    virtual ~ConfigManager();

    // IConfigManager interface
    void loadConfig(const QString &directory) override;
    const IGeneralConfig *getGeneralConfig() const override;
    QStringList serverList() const override;
    const IServerConfig *getServerConfig(const QString &name) const override;

protected:
    QHash<QString, IServerConfig *> &getServerConfigs();
    const QHash<QString, IServerConfig *> &getServerConfigs() const;

    virtual IServerConfig *createServerConfig(const QString &filePath);

private:
    bool mInitialized = false;
    QHash<QString, IServerConfig*> mServerConfigs;
    QScopedPointer<IGeneralConfig> mGeneralConfig;

    static const QString GENERAL_CONFIG_NAME,
                         CONFIG_DIRECTORY_NAME;
};

#endif // CONFIGMANAGER_H
