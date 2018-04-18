#ifndef SLEEPERADDON_H
#define SLEEPERADDON_H

#include "mcsmanager/config/configglobal.h"
#include "mcsmanager/mcserver/addons/sleeperconfigreader.h"
#include "mcserveraddonbase.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

class SleeperAddon : public QObject, public McServerAddonBase
{
    Q_OBJECT
public:
    SleeperAddon(IMcServer *server, QObject *parent = nullptr);
    ~SleeperAddon();

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
    int mPeriod;
    ConfigGlobal::ShutdownBehavior mShutdownBehavior;
    QString mAltServer;

    QTimer mTimer;
};

#endif // SLEEPERADDON_H