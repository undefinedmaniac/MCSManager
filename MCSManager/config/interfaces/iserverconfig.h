#ifndef ISERVERCONFIG_H
#define ISERVERCONFIG_H

#include <QString>

#include "iservermanagerconfig.h"
#include "iserverbackupconfig.h"
#include "ilogreaderaddonconfig.h"
#include "ibackupaddonconfig.h"
#include "isleeperaddonconfig.h"
#include "irestarteraddonconfig.h"
#include "imcscpaddonconfig.h"

class IServerConfig : public IServerManagerConfig, public IServerBackupConfig,
        public ILogReaderAddonConfig, public IBackupAddonConfig, public ISleeperAddonConfig,
        public IRestarterAddonConfig, public IMcscpAddonConfig
{
public:
    virtual ~IServerConfig() {}

    virtual QString name() const = 0;
    virtual QString javaPath() const = 0;
    virtual QString jarName() const = 0;
    virtual QString workingDirectory() const = 0;
    virtual QStringList arguments() const = 0;
    virtual QStringList enabledAddons() const = 0;
};

#endif // ISERVERCONFIG_H
