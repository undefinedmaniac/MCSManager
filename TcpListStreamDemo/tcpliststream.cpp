#include "tcpliststream.h"

TcpListStream::TcpListStream()
{
}

void TcpListStream::setSocket(QIODevice *socket)
{
    if (mSocket)
        disconnect(mSocket, 0, this, 0);

    if (socket)
        connect(socket, SIGNAL(readyRead()), SLOT(socketReadyRead()));

    mSocket = socket;
}

QIODevice *TcpListStream::getSocket()
{
    return mSocket;
}

void TcpListStream::writeList(const QStringList &list)
{
    const int listSize = list.size();

    QVector<int> headerData(listSize);

    //Concatinate the strings and grab the header positions
    QString message;
    for (int i = 0; i < listSize; i++) {
        int termStartPos = message.size();
        if (termStartPos != 0)
            headerData[i - 1] = termStartPos;

        message += list.at(i);
    }

    //Set the last header number to the total message size
    QByteArray messageBytes = message.toUtf8();
    const int totalMessageSize = messageBytes.size();
    headerData[listSize - 1] = totalMessageSize;

    //Convert the list of ints into a QString header
    QString header;
    header.reserve(listSize * 2);
    for (int i = 0; i < listSize; i++) {
        header += QString::number(headerData.at(i));

        if (i != listSize - 1)
            header += QChar('.');
        else
            header += QChar(' ');
    }

    //Build the final message
    QByteArray finalMessage;
    finalMessage.append(header);
    finalMessage.append(messageBytes);

    mSocket->write(finalMessage);
}

QStringList TcpListStream::readList()
{
    return mReceivedLists.dequeue();
}

QList<QStringList> TcpListStream::readAll()
{
    QList<QStringList> lists;

    for (int i = 0; i < mReceivedLists.size(); i++) {
        lists.append(readList());
    }

    return lists;
}

void TcpListStream::socketReadyRead()
{
    mSpaceSearchPos = mBuffer.size();
    mBuffer.append(mSocket->readAll());

    while (true) {
        if (mHeader.isEmpty()) {
            mSpaceLocation = mBuffer.indexOf(' ', mSpaceSearchPos);

            //Levae if we could not find a space
            if (mSpaceLocation == -1)
                return;

            if (!fetchHeader()) {
                resetReadData(-1);
                return;
            }

            //Figure out the length of the entire message
            mLength = mSpaceLocation + mHeader.back() + 1;
        }

        //Leave if we don't have all of the message yet
        if (mBuffer.size() < mLength)
            return;

        const QByteArray messageBytes = mBuffer.mid(mSpaceLocation + 1, mHeader.back());

        const QString message = QString::fromUtf8(messageBytes);

        QStringList list;
        list.reserve(mHeader.size());

        for (int i = 0; i < mHeader.size(); i++) {
            int startPos, endPos, length;

            if (i == 0)
                startPos = 0;
            else
                startPos = mHeader.at(i - 1);

            if (i == mHeader.size() - 1)
                endPos = message.size();
            else
                endPos = mHeader.at(i);

            length = endPos - startPos;

            const QString data = message.mid(startPos, length);
            list.append(data);
        }

        //Empty the buffer and header
        resetReadData(mLength);

        mReceivedLists.enqueue(list);
        emit readyRead();

        if (mBuffer.isEmpty())
            return;
    }
}

bool TcpListStream::fetchHeader()
{
    const QString header = QString::fromUtf8(mBuffer.left(mSpaceLocation));
    const QStringList headerData = header.split('.');
    const int headerDataSize = headerData.size();

    if (headerDataSize == 0)
        return false;

    mHeader.resize(headerDataSize);

    for (int i = 0; i < headerDataSize; i++) {
        int position = headerData.at(i).toInt();
        if (position != 0)
            mHeader[i] = position;
        else
            return false;
    }

    return true;
}

void TcpListStream::resetReadData(int bufferLength)
{
    mBuffer.remove(0, bufferLength);
    mHeader.clear();
    mHeader.squeeze();
    mSpaceSearchPos = 0;
}
