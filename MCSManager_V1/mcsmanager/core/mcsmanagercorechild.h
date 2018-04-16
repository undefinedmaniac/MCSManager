#ifndef MCSMANAGERCORECHILD_H
#define MCSMANAGERCORECHILD_H

#include "interfaces/imcsmanagercore.h"

class McsManagerCoreChild
{
public:
    McsManagerCoreChild(IMcsManagerCore *core);
    virtual ~McsManagerCoreChild() {}

protected:
    IMcsManagerCore *getCore();
    IConfigManager *getConfigManager();
    IBackupManager *getBackupManager();
    IMcServerBuilder *getServerBuilder();
    IMcServer *getCurrentServer();

private:
    IMcsManagerCore *mCore;
};

#endif // MCSMANAGERCORECHILD_H
