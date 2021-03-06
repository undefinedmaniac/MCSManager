#ifndef MCSCPSERVERTABLE_H
#define MCSCPSERVERTABLE_H

#include "interfaces/imcscpservertable.h"

#include <QObject>

namespace Mcscp { class McscpServerTable; }

class Mcscp::McscpServerTable : public IMcscpServerTable
{
    Q_OBJECT
public:
    McscpServerTable(QObject *parent = nullptr);

    void setMaxPlayers(int maxPlayers);
    void setPlayerCount(int playerCount);
    void setMotd(const QString &motd);
    void setTps(float tps);
    void setMaxRam(float getMaxRam);
    void setTotalRam(float getTotalRam);
    void setUsedRam(float getUsedRam);

    // IMcscpServerTable interface
    int getMaxPlayers() const override;
    int getPlayerCount() const override;
    QString getMotd() const override;
    float getTps() const override;
    float getMaxRam() const override;
    float getTotalRam() const override;
    float getUsedRam() const override;

private:
    int mMaxPlayers, mPlayerCount;
    QString mMotd;
    float mTps, mMaxRam, mTotalRam, mUsedRam;
};

#endif // MCSCPSERVERTABLE_H
