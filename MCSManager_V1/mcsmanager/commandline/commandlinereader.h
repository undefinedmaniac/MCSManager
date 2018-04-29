#ifndef COMMANDLINEREADER_H
#define COMMANDLINEREADER_H

#include <QObject>
#include <QThread>
#include <QTextStream>
#include <QTimer>

namespace Cli { class CommandLineReader; }

class Cli::CommandLineReader : public QObject
{
    Q_OBJECT
public:
    CommandLineReader(QObject *parent = nullptr);

    void start();

signals:
    void newCommand(QString command);

public slots:
    void startRunning();
    void stopRunning();

private slots:
    void run();

private:
    QThread mThread;
    QTextStream mInput;
    bool mContinue;
};

#endif // COMMANDLINEREADER_H
