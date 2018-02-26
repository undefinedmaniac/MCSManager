#ifndef MCSMANAGERMEDIATOR_H
#define MCSMANAGERMEDIATOR_H

#include <QObject>
#include <QDebug>

#include "core/interface/imcsmanagermediator.h"

class McsManagerMediator : public QObject, public IMcsManagerMediator
{
    Q_OBJECT
    Q_INTERFACES(IMcsManagerMediator)
public:
    McsManagerMediator(QObject *parent = nullptr);
    ~McsManagerMediator();
    void startApplication();
    void stopApplication();

signals:
    void started();
    void stopped();
    void fatalError(QString errorString);
};

#endif // MCSMANAGERMEDIATOR_H
