#include "mcscpplayertable.h"

McscpPlayerTable::McscpPlayerTable(QObject *object) : IMcscpPlayerTable(object)
{
}

void McscpPlayerTable::setName(const QString &name)
{
    mName = name;
    emit KeyUpdate(Name);
}

void McscpPlayerTable::setDisplayName(const QString &displayName)
{
    mDisplayName = displayName;
    emit KeyUpdate(DisplayName);
}

void McscpPlayerTable::setIpAddress(const QString &ipAddress)
{
    mIpAddress = ipAddress;
    emit KeyUpdate(IpAddress);
}

void McscpPlayerTable::setMaxHealth(float maxHealth)
{
    mMaxHealth = maxHealth;
    emit KeyUpdate(MaxHealth);
}

void McscpPlayerTable::setHealth(float health)
{
    mHealth = health;
    emit KeyUpdate(Health);
}

void McscpPlayerTable::setHunger(float hunger)
{
    mHunger = hunger;
    emit KeyUpdate(Hunger);
}

void McscpPlayerTable::setLevel(float level)
{
    mLevel = level;
    emit KeyUpdate(Level);
}

void McscpPlayerTable::setWorld(const QString &world)
{
    mWorld = world;
    emit KeyUpdate(World);
}

void McscpPlayerTable::alertPlayerDisconnected()
{
    emit playerDisconnected();
}

QString McscpPlayerTable::getName() const
{
    return mName;
}

QString McscpPlayerTable::getDisplayName() const
{
    return mDisplayName;
}

QString McscpPlayerTable::getIpAddress() const
{
    return mIpAddress;
}

float McscpPlayerTable::getMaxHealth() const
{
    return mMaxHealth;
}

float McscpPlayerTable::getHealth() const
{
    return mHealth;
}

float McscpPlayerTable::getHunger() const
{
    return mHunger;
}

float McscpPlayerTable::getLevel() const
{
    return mLevel;
}

QString McscpPlayerTable::getWorld() const
{
    return mWorld;
}
