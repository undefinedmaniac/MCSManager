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
    QByteArrayData data[19];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cli__CommandLine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cli__CommandLine_t qt_meta_stringdata_Cli__CommandLine = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Cli::CommandLine"
QT_MOC_LITERAL(1, 17, 7), // "started"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "stopped"
QT_MOC_LITERAL(4, 34, 15), // "exitApplication"
QT_MOC_LITERAL(5, 50, 10), // "newCommand"
QT_MOC_LITERAL(6, 61, 14), // "processCommand"
QT_MOC_LITERAL(7, 76, 13), // "backupStarted"
QT_MOC_LITERAL(8, 90, 6), // "server"
QT_MOC_LITERAL(9, 97, 14), // "backupFinished"
QT_MOC_LITERAL(10, 112, 11), // "backupError"
QT_MOC_LITERAL(11, 124, 11), // "errorString"
QT_MOC_LITERAL(12, 136, 20), // "currentServerChanged"
QT_MOC_LITERAL(13, 157, 13), // "serverStarted"
QT_MOC_LITERAL(14, 171, 13), // "serverStopped"
QT_MOC_LITERAL(15, 185, 8), // "expected"
QT_MOC_LITERAL(16, 194, 11), // "serverError"
QT_MOC_LITERAL(17, 206, 10), // "newLogData"
QT_MOC_LITERAL(18, 217, 11) // "startingPos"

    },
    "Cli::CommandLine\0started\0\0stopped\0"
    "exitApplication\0newCommand\0processCommand\0"
    "backupStarted\0server\0backupFinished\0"
    "backupError\0errorString\0currentServerChanged\0"
    "serverStarted\0serverStopped\0expected\0"
    "serverError\0newLogData\0startingPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cli__CommandLine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   77,    2, 0x08 /* Private */,
       7,    1,   80,    2, 0x08 /* Private */,
       9,    1,   83,    2, 0x08 /* Private */,
      10,    2,   86,    2, 0x08 /* Private */,
      12,    0,   91,    2, 0x08 /* Private */,
      13,    0,   92,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,
      16,    1,   96,    2, 0x08 /* Private */,
      17,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void Cli::CommandLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CommandLine *_t = static_cast<CommandLine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped(); break;
        case 2: _t->exitApplication(); break;
        case 3: _t->newCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->backupStarted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->backupFinished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->backupError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->currentServerChanged(); break;
        case 8: _t->serverStarted(); break;
        case 9: _t->serverStopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->serverError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->newLogData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CommandLine::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLine::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CommandLine::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLine::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CommandLine::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLine::exitApplication)) {
                *result = 2;
                return;
            }
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Cli::CommandLine::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Cli::CommandLine::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cli::CommandLine::exitApplication()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
