#ifndef MCSMANAGERCORECHILD_H
#define MCSMANAGERCORECHILD_H

#include "interfaces/imcsmanagercore.h"

namespace Core { class McsManagerCoreChild; }

class Core::McsManagerCoreChild
{
public:
    McsManagerCoreChild(IMcsManagerCore *core);
    virtual ~McsManagerCoreChild() {}

protected:
    Core::IMcsManagerCore *getCore();
    Config::IConfigManager *getConfigManager();
    Backup::IBackupManager *getBackupManager();
    Server::IMcServerBuilder *getServerBuilder();
    Server::IMcServer *getCurrentServer();

private:
    Core::IMcsManagerCore *mCore;
};

#endif // MCSMANAGERCORECHILD_H
