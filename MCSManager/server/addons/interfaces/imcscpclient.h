#ifndef IMCSCPCLIENT_H
#define IMCSCPCLIENT_H

class IMcscpCommand;
class IMcscpAddonConfig;

class IMcscpClient
{
public:
    enum McscpEvent {
        PlayerJoined, PlayerLeft
    };

    virtual ~IMcscpClient() {}

    virtual const IMcscpAddonConfig *config() const = 0;

    virtual void sendCmd(IMcscpCommand *cmd) = 0;

signals:
    virtual void serverEvent(McscpEvent event) = 0;
};

Q_DECLARE_INTERFACE(IMcscpClient, "IMcscpClient")

#endif // IMCSCPCLIENT_H
