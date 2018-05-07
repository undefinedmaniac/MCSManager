#ifndef IMCSCPPLAYERTABLE_H
#define IMCSCPPLAYERTABLE_H

#include <QObject>

namespace Mcscp { class IMcscpPlayerTable; }

class Mcscp::IMcscpPlayerTable : public QObject
{
    Q_OBJECT
public:
    IMcscpPlayerTable(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IMcscpPlayerTable() {}

    enum Key {
        Name, DisplayName, IpAddress, MaxHealth, Health,
        Hunger, Level, World
    };

    virtual QString getName() const = 0;
    virtual QString getDisplayName() const = 0;
    virtual QString getIpAddress() const = 0;
    virtual float getMaxHealth() const = 0;
    virtual float getHealth() const = 0;
    virtual float getHunger() const = 0;
    virtual float getLevel() const = 0;
    virtual QString getWorld() const = 0;

signals:
    void KeyUpdate(IMcscpPlayerTable::Key key);
    void playerDisconnected();
};

#endif // IMCSCPPLAYERTABLE_H
