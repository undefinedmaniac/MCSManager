#ifndef IENABLEDADDONS_H
#define IENABLEDADDONS_H

class QStringList;

class IEnabledAddons
{
public:
    virtual ~IEnabledAddons() {}

    virtual QStringList getEnabledAddons() = 0;
};

#endif // IENABLEDADDONS_H
