/****************************************************************************
** Meta object code from reading C++ file 'CentroidTracker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../NeoCrowdLib/Tracker/CentroidTracker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CentroidTracker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CentroidTracker_t {
    QByteArrayData data[5];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CentroidTracker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CentroidTracker_t qt_meta_stringdata_CentroidTracker = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CentroidTracker"
QT_MOC_LITERAL(1, 16, 8), // "UpdateID"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "stamp"
QT_MOC_LITERAL(4, 32, 2) // "id"

    },
    "CentroidTracker\0UpdateID\0\0stamp\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CentroidTracker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void CentroidTracker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CentroidTracker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->UpdateID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CentroidTracker::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseTracker::staticMetaObject>(),
    qt_meta_stringdata_CentroidTracker.data,
    qt_meta_data_CentroidTracker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CentroidTracker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CentroidTracker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CentroidTracker.stringdata0))
        return static_cast<void*>(this);
    return BaseTracker::qt_metacast(_clname);
}

int CentroidTracker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTracker::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
