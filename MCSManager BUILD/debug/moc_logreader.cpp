/****************************************************************************
** Meta object code from reading C++ file 'logreader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager/server/addons/logreader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logreader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LogReader_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogReader_t qt_meta_stringdata_LogReader = {
    {
QT_MOC_LITERAL(0, 0, 9), // "LogReader"
QT_MOC_LITERAL(1, 10, 7), // "newData"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "startPos"
QT_MOC_LITERAL(4, 28, 23), // "readyReadStandardOutput"
QT_MOC_LITERAL(5, 52, 22), // "readyReadStandardError"
QT_MOC_LITERAL(6, 75, 8) // "testSlot"

    },
    "LogReader\0newData\0\0startPos\0"
    "readyReadStandardOutput\0readyReadStandardError\0"
    "testSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void LogReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LogReader *_t = static_cast<LogReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->readyReadStandardOutput(); break;
        case 2: _t->readyReadStandardError(); break;
        case 3: _t->testSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LogReader::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LogReader::newData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LogReader::staticMetaObject = {
    { &MinecraftServerAddonBase::staticMetaObject, qt_meta_stringdata_LogReader.data,
      qt_meta_data_LogReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LogReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LogReader.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ILogReader"))
        return static_cast< ILogReader*>(this);
    if (!strcmp(_clname, "ILogReader"))
        return static_cast< ILogReader*>(this);
    return MinecraftServerAddonBase::qt_metacast(_clname);
}

int LogReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MinecraftServerAddonBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LogReader::newData(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
