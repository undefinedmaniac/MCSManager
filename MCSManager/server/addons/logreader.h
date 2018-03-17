#ifndef LOGREADER_H
#define LOGREADER_H

#include <QObject>
#include <QDebug>

#include "config/interfaces/iserverconfig.h"

#include "server/addons/minecraftserveraddonbase.h"
#include "server/interfaces/iminecraftserver.h"
#include "server/addons/interfaces/ilogreader.h"

class LogReader : public QObject, public MinecraftServerAddonBase, public ILogReader
{
    Q_OBJECT
    Q_INTERFACES(ILogReader)
public:
    LogReader(const QString &name, IMinecraftServer *server);
    ~LogReader();

    // IMinecraftServerAddon interface
    void start() override;
    void stop() override;
    bool isRunning() override;

    // ILogReader interface
    const ILogReaderAddonConfig *config() const override;

    QByteArray readAll(int startPos = 0) const override;
    int size() const override;
    void clear() override;

signals:
    void newData(int startPos) override;

private slots:
    void readyReadStandardOutput();
    void readyReadStandardError();
    void testSlot(int startPos);

private:
    QByteArray mData;
    bool mRunning = false;
};

#endif // LOGREADER_H
