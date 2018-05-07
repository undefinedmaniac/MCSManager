#ifndef ITCPLISTSTREAM_H
#define ITCPLISTSTREAM_H

#include <QObject>

class QIODevice;

class ITcpListStream : public QObject
{
    Q_OBJECT
public:
    virtual void setSocket(QIODevice *socket) = 0;
    virtual QIODevice *getSocket() = 0;

    virtual void writeList(const QStringList &list) = 0;
    virtual QStringList readList() = 0;
    virtual QList<QStringList> readAll() = 0;

signals:
    void readyRead();
    void listWritten();
};

#endif // ITCPLISTSTREAM_H
