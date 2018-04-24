#ifndef IMCSERVERBUILDER_H
#define IMCSERVERBUILDER_H

class IMcServer;
class IServerConfig;

class IMcServerBuilder
{
public:
    virtual ~IMcServerBuilder() {}

    virtual IMcServer *getMcServer(IServerConfig *serverConfig) = 0;
    virtual void deleteMcServer(IMcServer *server) = 0;
};

#endif // IMCSERVERBUILDER_H
