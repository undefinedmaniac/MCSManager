/****************************************************************************
** Meta object code from reading C++ file 'backupmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/backup/backupmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Backup__BackupManager_t {
    QByteArrayData data[6];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Backup__BackupManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Backup__BackupManager_t qt_meta_stringdata_Backup__BackupManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Backup::BackupManager"
QT_MOC_LITERAL(1, 22, 14), // "processStarted"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 15), // "processFinished"
QT_MOC_LITERAL(4, 54, 12), // "processError"
QT_MOC_LITERAL(5, 67, 11) // "errorString"

    },
    "Backup::BackupManager\0processStarted\0"
    "\0processFinished\0processError\0errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Backup__BackupManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void Backup::BackupManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackupManager *_t = static_cast<BackupManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processStarted(); break;
        case 1: _t->processFinished(); break;
        case 2: _t->processError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Backup::BackupManager::staticMetaObject = {
    { &Backup::IBackupManager::staticMetaObject, qt_meta_stringdata_Backup__BackupManager.data,
      qt_meta_data_Backup__BackupManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Backup::BackupManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backup::BackupManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Backup__BackupManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Core::McsManagerCoreChild"))
        return static_cast< Core::McsManagerCoreChild*>(this);
    return Backup::IBackupManager::qt_metacast(_clname);
}

int Backup::BackupManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Backup::IBackupManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
