#ifndef IBACKUPPROCESS_H
#define IBACKUPPROCESS_H

#include <QObject>

class IBackupProcess : public QObject
{
    Q_OBJECT
public:
    IBackupProcess(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IBackupProcess() {}

    virtual void start() = 0;
    virtual bool isRunning() const = 0;

signals:
    void aboutToStart();
    void finished();
    void error();
};

#endif // IBACKUPPROCESS_H
