#ifndef IMINECRAFTSERVERIO_H
#define IMINECRAFTSERVERIO_H

#include <QByteArray>

class IMinecraftServerIo
{
public:
    virtual ~IMinecraftServerIo() {}

    virtual QByteArray readAllStandardOutput() = 0;
    virtual QByteArray readAllStandardError() = 0;
    virtual int write(const QByteArray &data) = 0;

signals:
    virtual void readyReadStandardOutput() = 0;
    virtual void readyReadStandardError() = 0;
    virtual void bytesWritten(qint64 bytes) = 0;
};

Q_DECLARE_INTERFACE(IMinecraftServerIo, "IMinecraftServerIo")

#endif // IMINECRAFTSERVERIO_H
