#ifndef RESTARTERSERVICE_H
#define RESTARTERSERVICE_H

#include <QDebug>
#include <QTimer>
#include <QObject>

#include "server/minecraftserver.h"

#include "server/addons/minecraftserveraddonbase.h"
#include "server/addons/interfaces/irestarterservice.h"
#include "server/manager/interfaces/iminecraftservermanager.h"

class RestarterService : public MinecraftServerAddonBase, public IRestarterService
{
    Q_OBJECT
public:
    RestarterService(const QString &name, IMinecraftServer *server);

    // IMinecraftServerAddon interface
    void start() override;
    void stop() override;
    bool isRunning() override;

    // IRestarterService interface
    const IRestarterAddonConfig *config() const override;
    int timeUntilRestart() const override;

private slots:
    void timeout();

private:
    QTimer mTimer;
};

#endif // RESTARTERSERVICE_H
