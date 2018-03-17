/****************************************************************************
** Meta object code from reading C++ file 'minecraftserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager/server/minecraftserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minecraftserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinecraftServer_t {
    QByteArrayData data[14];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinecraftServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinecraftServer_t qt_meta_stringdata_MinecraftServer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MinecraftServer"
QT_MOC_LITERAL(1, 16, 7), // "started"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "stopped"
QT_MOC_LITERAL(4, 33, 5), // "error"
QT_MOC_LITERAL(5, 39, 11), // "errorString"
QT_MOC_LITERAL(6, 51, 23), // "readyReadStandardOutput"
QT_MOC_LITERAL(7, 75, 22), // "readyReadStandardError"
QT_MOC_LITERAL(8, 98, 12), // "bytesWritten"
QT_MOC_LITERAL(9, 111, 5), // "bytes"
QT_MOC_LITERAL(10, 117, 13), // "errorOccurred"
QT_MOC_LITERAL(11, 131, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(12, 154, 13), // "serverStarted"
QT_MOC_LITERAL(13, 168, 13) // "serverStopped"

    },
    "MinecraftServer\0started\0\0stopped\0error\0"
    "errorString\0readyReadStandardOutput\0"
    "readyReadStandardError\0bytesWritten\0"
    "bytes\0errorOccurred\0QProcess::ProcessError\0"
    "serverStarted\0serverStopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinecraftServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       6,    0,   64,    2, 0x06 /* Public */,
       7,    0,   65,    2, 0x06 /* Public */,
       8,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   69,    2, 0x08 /* Private */,
      12,    0,   72,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MinecraftServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinecraftServer *_t = static_cast<MinecraftServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped(); break;
        case 2: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->readyReadStandardOutput(); break;
        case 4: _t->readyReadStandardError(); break;
        case 5: _t->bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->errorOccurred((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 7: _t->serverStarted(); break;
        case 8: _t->serverStopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MinecraftServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MinecraftServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MinecraftServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::error)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MinecraftServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::readyReadStandardOutput)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MinecraftServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::readyReadStandardError)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MinecraftServer::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinecraftServer::bytesWritten)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MinecraftServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MinecraftServer.data,
      qt_meta_data_MinecraftServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MinecraftServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinecraftServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinecraftServer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IMinecraftServer"))
        return static_cast< IMinecraftServer*>(this);
    if (!strcmp(_clname, "IMinecraftServer"))
        return static_cast< IMinecraftServer*>(this);
    return QObject::qt_metacast(_clname);
}

int MinecraftServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MinecraftServer::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MinecraftServer::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MinecraftServer::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MinecraftServer::readyReadStandardOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MinecraftServer::readyReadStandardError()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MinecraftServer::bytesWritten(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
