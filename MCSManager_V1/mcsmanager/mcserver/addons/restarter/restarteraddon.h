#ifndef RESTARTERADDON_H
#define RESTARTERADDON_H

#include "mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include "mcsmanager/config/configglobal.h"
#include "restarterconfigreader.h"
#include "../mcserveraddonbase.h"

#include <QObject>
#include <QTimer>

class RestarterAddon : public QObject, public McServerAddonBase
{
    Q_OBJECT
public:
    RestarterAddon(IMcServer *server, QObject *parent = nullptr);

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
    IMcscpAddon *mMcscpAddon = nullptr;

    QTimer mTimer;
    int mSeconds;

    QString getBroadcastMessage();
};

#endif // RESTARTERADDON_H
