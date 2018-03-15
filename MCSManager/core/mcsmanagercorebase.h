#ifndef MCSMANAGERCOREBASE_H
#define MCSMANAGERCOREBASE_H

#include "core/interfaces/imcsmanagercorebase.h"

class IMcsManagerCore;

class McsManagerCoreBase : public IMcsManagerCoreBase
{
public:
    McsManagerCoreBase(IMcsManagerCore *core = nullptr);
    virtual ~McsManagerCoreBase() {}

    void setCore(IMcsManagerCore *core) override;
    IMcsManagerCore *getCore() override;

private:
    IMcsManagerCore *mCore;
};

#endif // MCSMANAGERCOREBASE_H
