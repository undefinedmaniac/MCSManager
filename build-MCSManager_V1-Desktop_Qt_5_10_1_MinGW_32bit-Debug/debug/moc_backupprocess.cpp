/****************************************************************************
** Meta object code from reading C++ file 'backupprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MCSManager_V1/mcsmanager/backup/backupprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Backup__BackupProcess_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Backup__BackupProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Backup__BackupProcess_t qt_meta_stringdata_Backup__BackupProcess = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Backup::BackupProcess"
QT_MOC_LITERAL(1, 22, 12), // "stepFinished"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "processError"
QT_MOC_LITERAL(4, 49, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(5, 72, 9) // "errorType"

    },
    "Backup::BackupProcess\0stepFinished\0\0"
    "processError\0QProcess::ProcessError\0"
    "errorType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Backup__BackupProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    1,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void Backup::BackupProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackupProcess *_t = static_cast<BackupProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stepFinished(); break;
        case 1: _t->processError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Backup::BackupProcess::staticMetaObject = {
    { &Backup::IBackupProcess::staticMetaObject, qt_meta_stringdata_Backup__BackupProcess.data,
      qt_meta_data_Backup__BackupProcess,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Backup::BackupProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backup::BackupProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Backup__BackupProcess.stringdata0))
        return static_cast<void*>(this);
    return Backup::IBackupProcess::qt_metacast(_clname);
}

int Backup::BackupProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Backup::IBackupProcess::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
