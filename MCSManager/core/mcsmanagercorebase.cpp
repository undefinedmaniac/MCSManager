#include "mcsmanagercorebase.h"

McsManagerCoreBase::McsManagerCoreBase(IMcsManagerCore *core) : mCore(core)
{

}

void McsManagerCoreBase::setCore(IMcsManagerCore *core)
{
    mCore = core;
}

IMcsManagerCore *McsManagerCoreBase::getCore()
{
    return mCore;
}
