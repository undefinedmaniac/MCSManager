#include "logreader.h"

LogReader::LogReader(const QString &name, IMinecraftServer *server) : MinecraftServerAddonBase(name, server)
{
    QObject *object = dynamic_cast<QObject *>(server);

    QObject::connect(object, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    QObject::connect(object, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
    QObject::connect(object, SIGNAL(stopped()), this, SLOT(serverStopped()));
    QObject::connect(this, SIGNAL(newData(int)), this, SLOT(testSlot(int)));
}

void LogReader::start()
{
    qDebug() << "Log Reader Started!";
    mRunning = true;
}

void LogReader::stop()
{
    qDebug() << "Log Reader Stopped!";
    mRunning = false;
}

bool LogReader::isRunning()
{
    return mRunning;
}

void LogReader::setConfig(const ILogReaderAddonConfig *config)
{
    mConfig = config;
}

const ILogReaderAddonConfig *LogReader::config() const
{
    return mConfig;
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

void LogReader::serverStopped()
{
    clear();
}

void LogReader::testSlot(int startPos)
{
    qDebug() << "New Data at: " << startPos;
    qDebug() << "Data: " << readAll(startPos);
}
