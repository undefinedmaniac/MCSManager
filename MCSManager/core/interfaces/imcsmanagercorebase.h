#ifndef IMCSMANAGERCOREBASE_H
#define IMCSMANAGERCOREBASE_H

class IMcsManagerCore;

class IMcsManagerCoreBase
{
public:
    virtual ~IMcsManagerCoreBase() {}

    virtual void setCore(IMcsManagerCore *core) = 0;
    virtual IMcsManagerCore *getCore() = 0;
};

#endif // IMCSMANAGERCOREBASE_H
