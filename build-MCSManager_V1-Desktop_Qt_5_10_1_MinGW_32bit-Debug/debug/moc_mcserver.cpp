/****************************************************************************
** Meta object code from reading C++ file 'mcserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/mcserver/server/mcserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_McServer_t {
    QByteArrayData data[15];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_McServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_McServer_t qt_meta_stringdata_McServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "McServer"
QT_MOC_LITERAL(1, 9, 7), // "started"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "stopped"
QT_MOC_LITERAL(4, 26, 8), // "expected"
QT_MOC_LITERAL(5, 35, 5), // "error"
QT_MOC_LITERAL(6, 41, 12), // "errorMessage"
QT_MOC_LITERAL(7, 54, 13), // "serverStarted"
QT_MOC_LITERAL(8, 68, 13), // "serverStopped"
QT_MOC_LITERAL(9, 82, 8), // "exitCode"
QT_MOC_LITERAL(10, 91, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(11, 112, 10), // "exitStatus"
QT_MOC_LITERAL(12, 123, 19), // "serverErrorOccurred"
QT_MOC_LITERAL(13, 143, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(14, 166, 9) // "errorType"

    },
    "McServer\0started\0\0stopped\0expected\0"
    "error\0errorMessage\0serverStarted\0"
    "serverStopped\0exitCode\0QProcess::ExitStatus\0"
    "exitStatus\0serverErrorOccurred\0"
    "QProcess::ProcessError\0errorType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_McServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x08 /* Private */,
       8,    2,   52,    2, 0x08 /* Private */,
      12,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void McServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        McServer *_t = static_cast<McServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->serverStarted(); break;
        case 4: _t->serverStopped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 5: _t->serverErrorOccurred((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (McServer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McServer::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (McServer::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McServer::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (McServer::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McServer::error)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject McServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_McServer.data,
      qt_meta_data_McServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *McServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *McServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_McServer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IMcServer"))
        return static_cast< IMcServer*>(this);
    if (!strcmp(_clname, "McsManagerCoreChild"))
        return static_cast< McsManagerCoreChild*>(this);
    return QObject::qt_metacast(_clname);
}

int McServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void McServer::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void McServer::stopped(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void McServer::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
