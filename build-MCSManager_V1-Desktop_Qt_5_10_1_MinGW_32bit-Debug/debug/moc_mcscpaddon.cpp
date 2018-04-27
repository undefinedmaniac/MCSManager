/****************************************************************************
** Meta object code from reading C++ file 'mcscpaddon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/mcserver/addons/mcscp/mcscpaddon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcscpaddon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mcscp__McscpAddon_t {
    QByteArrayData data[8];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mcscp__McscpAddon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mcscp__McscpAddon_t qt_meta_stringdata_Mcscp__McscpAddon = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Mcscp::McscpAddon"
QT_MOC_LITERAL(1, 18, 17), // "attemptConnection"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "clientConnected"
QT_MOC_LITERAL(4, 53, 18), // "clientDisconnected"
QT_MOC_LITERAL(5, 72, 5), // "error"
QT_MOC_LITERAL(6, 78, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 107, 9) // "readyRead"

    },
    "Mcscp::McscpAddon\0attemptConnection\0"
    "\0clientConnected\0clientDisconnected\0"
    "error\0QAbstractSocket::SocketError\0"
    "readyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mcscp__McscpAddon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    5,
    QMetaType::Void,

       0        // eod
};

void Mcscp::McscpAddon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        McscpAddon *_t = static_cast<McscpAddon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attemptConnection(); break;
        case 1: _t->clientConnected(); break;
        case 2: _t->clientDisconnected(); break;
        case 3: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->readyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mcscp::McscpAddon::staticMetaObject = {
    { &IMcscpAddon::staticMetaObject, qt_meta_stringdata_Mcscp__McscpAddon.data,
      qt_meta_data_Mcscp__McscpAddon,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mcscp::McscpAddon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mcscp::McscpAddon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mcscp__McscpAddon.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Addon::McServerAddonBase"))
        return static_cast< Addon::McServerAddonBase*>(this);
    return IMcscpAddon::qt_metacast(_clname);
}

int Mcscp::McscpAddon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IMcscpAddon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
