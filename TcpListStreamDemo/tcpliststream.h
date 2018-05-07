#ifndef TCPLISTSTREAM_H
#define TCPLISTSTREAM_H

#include "itcpliststream.h"

#include <QIODevice>
#include <QQueue>
#include <QVector>
#include <QDebug>

class TcpListStream : public ITcpListStream
{
    Q_OBJECT
public:
    TcpListStream();

    // ITcpListStream interface
    void setSocket(QIODevice *socket) override;
    QIODevice *getSocket() override;

    void writeList(const QStringList &list) override;
    QStringList readList() override;
    QList<QStringList> readAll() override;

private slots:
    void socketReadyRead();

private:
    QIODevice *mSocket = nullptr;

    QQueue<QStringList> mReceivedLists;

    QByteArray mBuffer;
    int mSpaceSearchPos = 0;
    int mSpaceLocation, mLength;
    QVector<int> mHeader;

    bool fetchHeader();
    void resetReadData(int bufferLength);
};

#endif // TCPLISTSTREAM_H
