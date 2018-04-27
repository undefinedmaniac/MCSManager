#ifndef SLEEPERADDON_H
#define SLEEPERADDON_H

#include "../mcserveraddonbase.h"
#include "../mcscp/interfaces/imcscpservertable.h"
#include "../mcscp/interfaces/imcscpplayertable.h"
#include "../mcscp/interfaces/imcscpaddon.h"
#include "sleeperconfigreader.h"
#include "mcsmanager/config/interfaces/iserverconfig.h"
#include "mcsmanager/mcserver/addons/mcscp/mcscpglobal.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

namespace Sleeper { class SleeperAddon; }

class Sleeper::SleeperAddon : public QObject, public Addon::McServerAddonBase
{
    Q_OBJECT
public:
    SleeperAddon(Server::IMcServer *server, QObject *parent = nullptr);

    // IMcServerAddon interface
    void preInit() override;
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() const override;

public slots:
    void playerCountChanged(IMcscpServerTable::Key key);
    void sleepTimerExpired();
    void mcscpConnected();
    void mcscpDisconnected();

private:
    bool mIsRunning = false;

    bool mConfigIsValid = false;
    int mPeriod;
    Config::ShutdownBehavior mShutdownBehavior;
    QString mAltServer;

    const IMcscpServerTable *mTable = nullptr;

    QTimer mTimer;

    void checkPlayerCount();
};

#endif // SLEEPERADDON_H
