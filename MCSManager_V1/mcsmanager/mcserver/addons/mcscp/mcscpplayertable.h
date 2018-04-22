#ifndef MCSCPPLAYERTABLE_H
#define MCSCPPLAYERTABLE_H

#include "interfaces/imcscpplayertable.h"

#include <QDebug>

class McscpPlayerTable : public IMcscpPlayerTable
{
    Q_OBJECT
public:
    McscpPlayerTable(QObject *object = nullptr);

    void setName(const QString &name);
    void setDisplayName(const QString &displayName);
    void setIpAddress(const QString &ipAddress);
    void setMaxHealth(float maxHealth);
    void setHealth(float health);
    void setHunger(float hunger);
    void setLevel(float level);
    void setWorld(const QString &world);

    void alertPlayerDisconnected();

    // IMcscPlayerTable interface
    QString getName() const override;
    QString getDisplayName() const override;
    QString getIpAddress() const override;
    float getMaxHealth() const override;
    float getHealth() const override;
    float getHunger() const override;
    float getLevel() const override;
    QString getWorld() const override;

private:
    QString mName, mDisplayName, mIpAddress, mWorld;
    float mMaxHealth, mHealth, mHunger, mLevel;
};

#endif // MCSCPPLAYERTABLE_H
