/****************************************************************************
** Meta object code from reading C++ file 'mcsmanagercore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager/core/mcsmanagercore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcsmanagercore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_McsManagerCore_t {
    QByteArrayData data[12];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_McsManagerCore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_McsManagerCore_t qt_meta_stringdata_McsManagerCore = {
    {
QT_MOC_LITERAL(0, 0, 14), // "McsManagerCore"
QT_MOC_LITERAL(1, 15, 7), // "started"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "name"
QT_MOC_LITERAL(4, 29, 7), // "stopped"
QT_MOC_LITERAL(5, 37, 10), // "logUpdated"
QT_MOC_LITERAL(6, 48, 5), // "event"
QT_MOC_LITERAL(7, 54, 24), // "IMcscpClient::McscpEvent"
QT_MOC_LITERAL(8, 79, 4), // "stop"
QT_MOC_LITERAL(9, 84, 9), // "forceStop"
QT_MOC_LITERAL(10, 94, 7), // "restart"
QT_MOC_LITERAL(11, 102, 12) // "forceRestart"

    },
    "McsManagerCore\0started\0\0name\0stopped\0"
    "logUpdated\0event\0IMcscpClient::McscpEvent\0"
    "stop\0forceStop\0restart\0forceRestart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_McsManagerCore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    0,   60,    2, 0x06 /* Public */,
       6,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   64,    2, 0x0a /* Public */,
       9,    0,   65,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void McsManagerCore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        McsManagerCore *_t = static_cast<McsManagerCore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->stopped((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->logUpdated(); break;
        case 3: _t->event((*reinterpret_cast< IMcscpClient::McscpEvent(*)>(_a[1]))); break;
        case 4: _t->stop(); break;
        case 5: _t->forceStop(); break;
        case 6: _t->restart(); break;
        case 7: _t->forceRestart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (McsManagerCore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McsManagerCore::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (McsManagerCore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McsManagerCore::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (McsManagerCore::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McsManagerCore::logUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (McsManagerCore::*_t)(IMcscpClient::McscpEvent );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McsManagerCore::event)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject McsManagerCore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_McsManagerCore.data,
      qt_meta_data_McsManagerCore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *McsManagerCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *McsManagerCore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_McsManagerCore.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IMcsManagerCore"))
        return static_cast< IMcsManagerCore*>(this);
    if (!strcmp(_clname, "IMcsManagerCore"))
        return static_cast< IMcsManagerCore*>(this);
    return QObject::qt_metacast(_clname);
}

int McsManagerCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void McsManagerCore::started(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void McsManagerCore::stopped(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void McsManagerCore::logUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void McsManagerCore::event(IMcscpClient::McscpEvent _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
