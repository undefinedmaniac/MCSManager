/****************************************************************************
** Meta object code from reading C++ file 'commandline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/commandline/commandline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commandline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cli__CommandLine_t {
    QByteArrayData data[16];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cli__CommandLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cli__CommandLine_t qt_meta_stringdata_Cli__CommandLine = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Cli::CommandLine"
QT_MOC_LITERAL(1, 17, 10), // "newCommand"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "processCommand"
QT_MOC_LITERAL(4, 44, 13), // "backupStarted"
QT_MOC_LITERAL(5, 58, 6), // "server"
QT_MOC_LITERAL(6, 65, 14), // "backupFinished"
QT_MOC_LITERAL(7, 80, 11), // "backupError"
QT_MOC_LITERAL(8, 92, 11), // "errorString"
QT_MOC_LITERAL(9, 104, 20), // "currentServerChanged"
QT_MOC_LITERAL(10, 125, 13), // "serverStarted"
QT_MOC_LITERAL(11, 139, 13), // "serverStopped"
QT_MOC_LITERAL(12, 153, 8), // "expected"
QT_MOC_LITERAL(13, 162, 11), // "serverError"
QT_MOC_LITERAL(14, 174, 10), // "newLogData"
QT_MOC_LITERAL(15, 185, 11) // "startingPos"

    },
    "Cli::CommandLine\0newCommand\0\0"
    "processCommand\0backupStarted\0server\0"
    "backupFinished\0backupError\0errorString\0"
    "currentServerChanged\0serverStarted\0"
    "serverStopped\0expected\0serverError\0"
    "newLogData\0startingPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cli__CommandLine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    2,   68,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    1,   75,    2, 0x08 /* Private */,
      13,    1,   78,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void Cli::CommandLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CommandLine *_t = static_cast<CommandLine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->backupStarted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->backupFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->backupError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->currentServerChanged(); break;
        case 5: _t->serverStarted(); break;
        case 6: _t->serverStopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->serverError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->newLogData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Cli::CommandLine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cli__CommandLine.data,
      qt_meta_data_Cli__CommandLine,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cli::CommandLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cli::CommandLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cli__CommandLine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Cli::CommandLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
