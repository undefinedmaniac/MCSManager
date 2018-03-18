#include "logreader.h"

LogReader::LogReader(const QString &name, IMinecraftServer *server) : MinecraftServerAddonBase(name, server)
{
    QObject *object = dynamic_cast<QObject *>(server);

    if (object != nullptr) {
        QObject::connect(object, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
        QObject::connect(object, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
        QObject::connect(this, SIGNAL(newData(int)), this, SLOT(testSlot(int)));
    }
}

LogReader::~LogReader()
{
    qDebug() << "Log Reader Deleted!";
}

void LogReader::start()
{
    qDebug() << "Log Reader Started!";
    mRunning = true;
}

void LogReader::stop()
{
    clear();
    qDebug() << "Log Reader Stopped!";
    mRunning = false;
}

bool LogReader::isRunning()
{
    return mRunning;
}

const ILogReaderAddonConfig *LogReader::config() const
{
    return server()->config();
}

QByteArray LogReader::readAll(int startPos) const
{
    return mData.mid(startPos);
}

int LogReader::size() const
{
    return mData.size();
}

void LogReader::clear()
{
    mData.clear();
}

void LogReader::readyReadStandardOutput()
{
    int startPos = size();
    mData.append(server()->readAllStandardOutput());
    emit newData(startPos);
}

void LogReader::readyReadStandardError()
{
    int startPos = size();
    mData.append(server()->readAllStandardError());
    emit newData(startPos);
}

void LogReader::testSlot(int startPos)
{
    qDebug() << "New Data at: " << startPos;
    qDebug() << "Data: " << readAll(startPos);
}
