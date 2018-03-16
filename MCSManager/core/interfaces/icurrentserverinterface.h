#ifndef ICURRENTSERVERINTERFACE_H
#define ICURRENTSERVERINTERFACE_H

#include "server/addons/interfaces/imcscpclient.h"

class QString;
class QByteArray;
class IServerConfig;
class IMcscpCommand;

class ICurrentServerInterface
{
public:
    virtual ~ICurrentServerInterface() {}

    virtual QString name() const = 0;
    virtual const IServerConfig *config() const = 0;

    virtual void sendChatMsg(const QString &playerName, const QByteArray &message) = 0;
    virtual void sendMcscpCmd(IMcscpCommand *cmd) = 0;

    virtual void stop() = 0;
    virtual void forceStop() = 0;
    virtual void restart() = 0;
    virtual void forceRestart() = 0;

    virtual QByteArray readAllLogData() const = 0;
    virtual QByteArray readNewLogData() = 0;

signals:
    virtual void started(QString name) = 0;
    virtual void stopped(QString name) = 0;

    virtual void logUpdated() = 0;
    virtual void event(IMcscpClient::McscpEvent event) = 0;
};

Q_DECLARE_INTERFACE(ICurrentServerInterface, "ICurrentServerInterface")

#endif // ICURRENTSERVERINTERFACE_H
