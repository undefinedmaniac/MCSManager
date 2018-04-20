#include "mcscpplayerreport.h"

McscpPlayerReport::McscpPlayerReport()
{ 
}

void McscpPlayerReport::setName(const QString &name)
{
    mName = name;
}

void McscpPlayerReport::setIp(const QString &ip)
{
    mIp = ip;
}

void McscpPlayerReport::setWorld(const QString &world)
{
    mWorld = world;
}

void McscpPlayerReport::setMaxHealth(float maxHealth)
{
    mMaxHealth = maxHealth;
}

void McscpPlayerReport::setHealth(float health)
{
    mHealth = health;
}

void McscpPlayerReport::setHunger(float hunger)
{
    mHunger = hunger;
}

void McscpPlayerReport::setLevel(float level)
{
    mLevel = level;
}

QString McscpPlayerReport::getName() const
{
    return mName;
}

QString McscpPlayerReport::getIp() const
{
    return mIp;
}

QString McscpPlayerReport::getWorld() const
{
    return mWorld;
}

float McscpPlayerReport::getMaxHealth() const
{
    return mMaxHealth;
}

float McscpPlayerReport::getHealth() const
{
    return mHealth;
}

float McscpPlayerReport::getHunger() const
{
    return mHunger;
}

float McscpPlayerReport::getLevel() const
{
    return mLevel;
}
