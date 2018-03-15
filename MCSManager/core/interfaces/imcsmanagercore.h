#ifndef IMCSMANAGERCORE_H
#define IMCSMANAGERCORE_H

#include "core/interfaces/imcsmanagerinterface.h"
#include "core/interfaces/icurrentserverinterface.h"

class IMcsManagerCore : public IMcsManagerInterface,
        public ICurrentServerInterface
{
public:
    virtual void startApplication() = 0;
};

Q_DECLARE_INTERFACE(IMcsManagerCore, "IMcsManagerCore")

#endif // IMCSMANAGERCORE_H
