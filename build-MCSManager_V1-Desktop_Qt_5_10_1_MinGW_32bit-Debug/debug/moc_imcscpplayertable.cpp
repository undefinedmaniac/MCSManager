/****************************************************************************
** Meta object code from reading C++ file 'imcscpplayertable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/mcserver/addons/mcscp/interfaces/imcscpplayertable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imcscpplayertable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mcscp__IMcscpPlayerTable_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mcscp__IMcscpPlayerTable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mcscp__IMcscpPlayerTable_t qt_meta_stringdata_Mcscp__IMcscpPlayerTable = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Mcscp::IMcscpPlayerTable"
QT_MOC_LITERAL(1, 25, 9), // "KeyUpdate"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 22), // "IMcscpPlayerTable::Key"
QT_MOC_LITERAL(4, 59, 3), // "key"
QT_MOC_LITERAL(5, 63, 18) // "playerDisconnected"

    },
    "Mcscp::IMcscpPlayerTable\0KeyUpdate\0\0"
    "IMcscpPlayerTable::Key\0key\0"
    "playerDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mcscp__IMcscpPlayerTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void Mcscp::IMcscpPlayerTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IMcscpPlayerTable *_t = static_cast<IMcscpPlayerTable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->KeyUpdate((*reinterpret_cast< IMcscpPlayerTable::Key(*)>(_a[1]))); break;
        case 1: _t->playerDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (IMcscpPlayerTable::*_t)(IMcscpPlayerTable::Key );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpPlayerTable::KeyUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (IMcscpPlayerTable::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IMcscpPlayerTable::playerDisconnected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mcscp::IMcscpPlayerTable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Mcscp__IMcscpPlayerTable.data,
      qt_meta_data_Mcscp__IMcscpPlayerTable,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mcscp::IMcscpPlayerTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mcscp::IMcscpPlayerTable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mcscp__IMcscpPlayerTable.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mcscp::IMcscpPlayerTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Mcscp::IMcscpPlayerTable::KeyUpdate(IMcscpPlayerTable::Key _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mcscp::IMcscpPlayerTable::playerDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
