#ifndef MCSCPPLAYERREPORT_H
#define MCSCPPLAYERREPORT_H

#include <QString>

class McscpPlayerReport
{
public:
    McscpPlayerReport();

    void setName(const QString &name);
    void setIp(const QString &ip);
    void setWorld(const QString &world);

    void setMaxHealth(float maxHealth);
    void setHealth(float health);
    void setHunger(float hunger);
    void setLevel(float level);

    QString getName() const;
    QString getIp() const;
    QString getWorld() const;

    float getMaxHealth() const;
    float getHealth() const;
    float getHunger() const;
    float getLevel() const;

private:
    QString mName, mIp, mWorld;
    float mMaxHealth, mHealth, mHunger, mLevel;
};

#endif // MCSCPPLAYERREPORT_H
