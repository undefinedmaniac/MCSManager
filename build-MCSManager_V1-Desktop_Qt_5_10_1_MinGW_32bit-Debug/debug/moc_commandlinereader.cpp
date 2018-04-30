/****************************************************************************
** Meta object code from reading C++ file 'commandlinereader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/commandline/commandlinereader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commandlinereader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cli__CommandLineReader_t {
    QByteArrayData data[8];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cli__CommandLineReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cli__CommandLineReader_t qt_meta_stringdata_Cli__CommandLineReader = {
    {
QT_MOC_LITERAL(0, 0, 22), // "Cli::CommandLineReader"
QT_MOC_LITERAL(1, 23, 7), // "started"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "stopped"
QT_MOC_LITERAL(4, 40, 10), // "newCommand"
QT_MOC_LITERAL(5, 51, 7), // "command"
QT_MOC_LITERAL(6, 59, 7), // "runLoop"
QT_MOC_LITERAL(7, 67, 9) // "readStdin"

    },
    "Cli::CommandLineReader\0started\0\0stopped\0"
    "newCommand\0command\0runLoop\0readStdin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cli__CommandLineReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    1,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Cli::CommandLineReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CommandLineReader *_t = static_cast<CommandLineReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped(); break;
        case 2: _t->newCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->runLoop(); break;
        case 4: _t->readStdin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CommandLineReader::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLineReader::started)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CommandLineReader::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLineReader::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CommandLineReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandLineReader::newCommand)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Cli::CommandLineReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cli__CommandLineReader.data,
      qt_meta_data_Cli__CommandLineReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cli::CommandLineReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cli::CommandLineReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cli__CommandLineReader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Cli::CommandLineReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Cli::CommandLineReader::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Cli::CommandLineReader::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cli::CommandLineReader::newCommand(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
