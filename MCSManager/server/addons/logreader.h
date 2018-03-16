#ifndef LOGREADER_H
#define LOGREADER_H

#include <QObject>
#include <QDebug>

#include "server/addons/minecraftserveraddonbase.h"
#include "server/interfaces/iminecraftserver.h"
#include "server/addons/interfaces/ilogreader.h"

class LogReader : public QObject, public MinecraftServerAddonBase, public ILogReader
{
    Q_OBJECT
    Q_INTERFACES(ILogReader)
public:
    LogReader(const QString &name, IMinecraftServer *server);

    // IMinecraftServerAddon interface
    void start() override;
    void stop() override;
    bool isRunning() override;

    // ILogReader interface
    void setConfig(const ILogReaderAddonConfig *config) override;
    const ILogReaderAddonConfig *config() const override;

    QByteArray readAll(int startPos = 0) const override;
    int size() const override;
    void clear() override;

signals:
    void newData(int startPos) override;

private slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void serverStopped();
    void testSlot(int startPos);

private:
    const ILogReaderAddonConfig *mConfig;
    QByteArray mData;
    bool mRunning = false;
};

#endif // LOGREADER_H
