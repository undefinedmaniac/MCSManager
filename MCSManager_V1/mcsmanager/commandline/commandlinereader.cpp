#include "commandlinereader.h"

using Cli::CommandLineReader;

CommandLineReader::CommandLineReader(QObject *parent) : QObject(parent), mInput(stdin, QIODevice::ReadOnly)
{
    this->moveToThread(&mThread);
    connect(&mThread, SIGNAL(started()), SLOT(runLoop()));
    connect(&mThread, SIGNAL(started()), SIGNAL(started()));
    connect(&mThread, SIGNAL(finished()), SIGNAL(stopped()));
}

void CommandLineReader::start()
{
    mMutex.lock();
    mContinue = true;
    mMutex.unlock();

    mThread.start();
}

void CommandLineReader::stop()
{
    mMutex.lock();
    mContinue = false;
    mMutex.unlock();
}

void CommandLineReader::runLoop()
{
    mMutex.lock();
    bool continueValue = mContinue;
    mMutex.unlock();

    if (continueValue)
        QTimer::singleShot(0, this, SLOT(readStdin()));
    else
        mThread.quit();
}

void CommandLineReader::readStdin()
{
    const QString command = mInput.readLine();
    emit newCommand(command);

    runLoop();
}
