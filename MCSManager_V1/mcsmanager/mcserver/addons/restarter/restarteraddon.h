#ifndef SLEEPERADDON_H
#define SLEEPERADDON_H

#include "mcsmanager/config/configglobal.h"
#include "restarterconfigreader.h"
#include "../mcserveraddonbase.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

class RestarterAddon : public QObject, public McServerAddonBase
{
    Q_OBJECT
public:
    RestarterAddon(IMcServer *server, QObject *parent = nullptr);
    ~RestarterAddon();

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
