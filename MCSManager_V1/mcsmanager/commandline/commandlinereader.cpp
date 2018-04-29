#include "commandlinereader.h"

using Cli::CommandLineReader;

CommandLineReader::CommandLineReader(QObject *parent) : QObject(parent), mInput(stdin)
{
    connect(&mThread, SIGNAL(started()), SLOT(startRunning()));
}

void CommandLineReader::start()
{
    this->moveToThread(&mThread);
    mThread.start();
}

void CommandLineReader::startRunning()
{
    mContinue = true;
    run();
}

void CommandLineReader::stopRunning()
{
    mContinue = false;
}

void CommandLineReader::run()
{
    if (!mInput.atEnd()) {
        const QString command = mInput.readLine();
        emit newCommand(command);
    }

    if (mContinue)
        QTimer::singleShot(0, this, SLOT(run()));
}
