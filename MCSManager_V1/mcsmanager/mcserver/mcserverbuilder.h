#ifndef MCSERVERBUILDER_H
#define MCSERVERBUILDER_H

#include "interfaces/imcserverbuilder.h"
#include "mcsmanager/core/mcsmanagercorechild.h"

#include <QVector>

class McServerBuilder : public IMcServerBuilder, public McsManagerCoreChild
{
public:
    McServerBuilder();

    // IMcServerBuilder interface
    IMcServer *getMcServer(IServerConfig *serverConfig) override;
    void deleteMcServer(IMcServer *server) override;

private:
    QVector<IMcServer*> mServers;

};

#endif // MCSERVERBUILDER_H
