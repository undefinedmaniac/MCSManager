#ifndef CONFIGGLOBAL_H
#define CONFIGGLOBAL_H

#include <QVector>
#include <QPair>

namespace ConfigGlobal {
typedef QVector<QPair<QString, QString>> ConfigData;
typedef QVector<QPair<QString, ConfigData>> DefaultList;

enum ShutdownBehavior {
    DoNothing, Restart, StartAltServer
};
}

#endif // CONFIGGLOBAL_H
