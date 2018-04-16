#ifndef SLEEPERADDON_H
#define SLEEPERADDON_H

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
    IConfigFile *mConfig;
    int mPeriod;

    QTimer mTimer;
};

#endif // SLEEPERADDON_H
