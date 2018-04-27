#ifndef RESTARTERADDON_H
#define RESTARTERADDON_H

#include "restarterglobal.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/config/configglobal.h"
#include "restarterconfigreader.h"
#include "../mcserveraddonbase.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

namespace Restarter { class RestarterAddon; }

class Restarter::RestarterAddon : public QObject, public Addon::McServerAddonBase
{
    Q_OBJECT
public:
    RestarterAddon(Server::IMcServer *server, QObject *parent = nullptr);

    // IMcServerAddon interface
    void preInit() override;
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void timeout();

private:
    bool mIsRunning = false;

    bool mConfigIsValid = false;
    int mPeriod;

    bool mMcscpAddonLocated = false;
    Mcscp::IMcscpAddon *mMcscpAddon = nullptr;

    QTimer mTimer;
    int mSeconds;

    QString getBroadcastMessage();
};

#endif // RESTARTERADDON_H
