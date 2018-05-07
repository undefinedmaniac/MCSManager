/****************************************************************************
** Meta object code from reading C++ file 'imcsmanagercore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/core/interfaces/imcsmanagercore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imcsmanagercore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core__IMcsManagerCore_t {
    QByteArrayData data[10];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core__IMcsManagerCore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core__IMcsManagerCore_t qt_meta_stringdata_Core__IMcsManagerCore = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Core::IMcsManagerCore"
QT_MOC_LITERAL(1, 22, 12), // "printMessage"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "message"
QT_MOC_LITERAL(4, 44, 20), // "currentServerChanged"
QT_MOC_LITERAL(5, 65, 13), // "backupStarted"
QT_MOC_LITERAL(6, 79, 6), // "server"
QT_MOC_LITERAL(7, 86, 14), // "backupFinished"
QT_MOC_LITERAL(8, 101, 11), // "backupError"
QT_MOC_LITERAL(9, 113, 11) // "errorString"

    },
    "Core::IMcsManagerCore\0printMessage\0\0"
    "message\0currentServerChanged\0backupStarted\0"
    "server\0backupFinished\0backupError\0"
    "errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core__IMcsManagerCore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,
       5,    1,   43,    2, 0x06 /* Public */,
       7,    1,   46,    2, 0x06 /* Public */,
       8,    2,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    9,

       0        // eod
};

void Core::IMcsManagerCore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IMcsManagerCore *_t = static_cast<IMcsManagerCore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->printMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->currentServerChanged(); break;
        case 2: _t->backupStarted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->backupFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->backupError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (IMcsManagerCore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcsManagerCore::printMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (IMcsManagerCore::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcsManagerCore::currentServerChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (IMcsManagerCore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcsManagerCore::backupStarted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (IMcsManagerCore::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcsManagerCore::backupFinished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (IMcsManagerCore::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcsManagerCore::backupError)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::IMcsManagerCore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Core__IMcsManagerCore.data,
      qt_meta_data_Core__IMcsManagerCore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Core::IMcsManagerCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::IMcsManagerCore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core__IMcsManagerCore.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::IMcsManagerCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Core::IMcsManagerCore::printMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::IMcsManagerCore::currentServerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Core::IMcsManagerCore::backupStarted(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Core::IMcsManagerCore::backupFinished(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Core::IMcsManagerCore::backupError(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
