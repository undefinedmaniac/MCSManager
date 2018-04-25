/****************************************************************************
** Meta object code from reading C++ file 'imcscpaddon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/mcserver/addons/mcscp/interfaces/imcscpaddon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imcscpaddon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IMcscpAddon_t {
    QByteArrayData data[13];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IMcscpAddon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IMcscpAddon_t qt_meta_stringdata_IMcscpAddon = {
    {
QT_MOC_LITERAL(0, 0, 11), // "IMcscpAddon"
QT_MOC_LITERAL(1, 12, 9), // "connected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "disconnected"
QT_MOC_LITERAL(4, 36, 12), // "playerJoined"
QT_MOC_LITERAL(5, 49, 4), // "uuid"
QT_MOC_LITERAL(6, 54, 10), // "playerLeft"
QT_MOC_LITERAL(7, 65, 10), // "playerDied"
QT_MOC_LITERAL(8, 76, 12), // "deathMessage"
QT_MOC_LITERAL(9, 89, 9), // "chatEvent"
QT_MOC_LITERAL(10, 99, 7), // "message"
QT_MOC_LITERAL(11, 107, 10), // "newLogData"
QT_MOC_LITERAL(12, 118, 11) // "startingPos"

    },
    "IMcscpAddon\0connected\0\0disconnected\0"
    "playerJoined\0uuid\0playerLeft\0playerDied\0"
    "deathMessage\0chatEvent\0message\0"
    "newLogData\0startingPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IMcscpAddon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,
       7,    2,   57,    2, 0x06 /* Public */,
       9,    2,   62,    2, 0x06 /* Public */,
      11,    1,   67,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void IMcscpAddon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IMcscpAddon *_t = static_cast<IMcscpAddon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->playerJoined((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->playerLeft((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->playerDied((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->chatEvent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->newLogData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (IMcscpAddon::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::playerJoined)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::playerLeft)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::playerDied)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::chatEvent)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (IMcscpAddon::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpAddon::newLogData)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IMcscpAddon::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IMcscpAddon.data,
      qt_meta_data_IMcscpAddon,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IMcscpAddon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IMcscpAddon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IMcscpAddon.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IMcscpAddon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void IMcscpAddon::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IMcscpAddon::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void IMcscpAddon::playerJoined(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IMcscpAddon::playerLeft(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IMcscpAddon::playerDied(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void IMcscpAddon::chatEvent(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void IMcscpAddon::newLogData(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
