#ifndef COMMANDLINEREADER_H
#define COMMANDLINEREADER_H

#include <QObject>
#include <QThread>
#include <QTextStream>
#include <QTimer>
#include <QMutex>
#include <QDebug>
#include <QMutexLocker>

namespace Cli { class CommandLineReader; }

class Cli::CommandLineReader : public QObject
{
    Q_OBJECT
public:
    CommandLineReader(QObject *parent = nullptr);

    void start();
    void stop();
    bool isRunning();

signals:
    void started();
    void stopped();
    void newCommand(QString command);

private slots:
    void runLoop();
    void readStdin();

private:
    QThread mThread;
    QTextStream mInput;
    QMutex mMutex;
    bool mContinue;
};

#endif // COMMANDLINEREADER_H
