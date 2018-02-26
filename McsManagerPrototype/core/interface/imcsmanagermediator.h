#ifndef IMCSMANAGERMEDIATOR_H
#define IMCSMANAGERMEDIATOR_H

#include <QString>

class IMcsManagerMediator
{
public:
    virtual ~IMcsManagerMediator() {}
    virtual void startApplication() = 0;
    virtual void stopApplication() = 0;

signals:
    virtual void started() = 0;
    virtual void stopped() = 0;
    virtual void fatalError(QString errorString) = 0;
};
Q_DECLARE_INTERFACE(IMcsManagerMediator, "IMcsManagerMediator")
#endif // IMCSMANAGERMEDIATOR_H
