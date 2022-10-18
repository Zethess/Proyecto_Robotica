/****************************************************************************
** Meta object code from reading C++ file 'specificworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../specificworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'specificworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpecificWorker_t {
    QByteArrayData data[18];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpecificWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpecificWorker_t qt_meta_stringdata_SpecificWorker = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SpecificWorker"
QT_MOC_LITERAL(1, 15, 7), // "compute"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "startup_check"
QT_MOC_LITERAL(4, 38, 10), // "initialize"
QT_MOC_LITERAL(5, 49, 6), // "period"
QT_MOC_LITERAL(6, 56, 16), // "FORWARD_function"
QT_MOC_LITERAL(7, 73, 23), // "std::tuple<float,float>"
QT_MOC_LITERAL(8, 97, 25), // "RoboCompLaser::TLaserData"
QT_MOC_LITERAL(9, 123, 5), // "ldata"
QT_MOC_LITERAL(10, 129, 13), // "IDLE_function"
QT_MOC_LITERAL(11, 143, 13), // "TURN_function"
QT_MOC_LITERAL(12, 157, 15), // "SPIRAL_function"
QT_MOC_LITERAL(13, 173, 18), // "follow_wall_method"
QT_MOC_LITERAL(14, 192, 19), // "hayQueSeguirLaPared"
QT_MOC_LITERAL(15, 212, 14), // "GirarIzquierda"
QT_MOC_LITERAL(16, 227, 18), // "calcularMediaLaser"
QT_MOC_LITERAL(17, 246, 5) // "laser"

    },
    "SpecificWorker\0compute\0\0startup_check\0"
    "initialize\0period\0FORWARD_function\0"
    "std::tuple<float,float>\0"
    "RoboCompLaser::TLaserData\0ldata\0"
    "IDLE_function\0TURN_function\0SPIRAL_function\0"
    "follow_wall_method\0hayQueSeguirLaPared\0"
    "GirarIzquierda\0calcularMediaLaser\0"
    "laser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpecificWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x0a /* Public */,
       6,    1,   74,    2, 0x0a /* Public */,
      10,    1,   77,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      12,    1,   83,    2, 0x0a /* Public */,
      13,    1,   86,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    5,
    0x80000000 | 7, 0x80000000 | 8,    9,
    0x80000000 | 7, 0x80000000 | 8,    9,
    0x80000000 | 7, 0x80000000 | 8,    9,
    0x80000000 | 7, 0x80000000 | 8,    9,
    0x80000000 | 7, 0x80000000 | 8,    9,
    QMetaType::Bool, 0x80000000 | 8,    9,
    QMetaType::Bool, 0x80000000 | 8,    9,
    QMetaType::Float, 0x80000000 | 8,   17,

       0        // eod
};

void SpecificWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpecificWorker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->compute(); break;
        case 1: { int _r = _t->startup_check();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->initialize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { std::tuple<float,float> _r = _t->FORWARD_function((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 4: { std::tuple<float,float> _r = _t->IDLE_function((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 5: { std::tuple<float,float> _r = _t->TURN_function((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 6: { std::tuple<float,float> _r = _t->SPIRAL_function((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 7: { std::tuple<float,float> _r = _t->follow_wall_method((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->hayQueSeguirLaPared((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->GirarIzquierda((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { float _r = _t->calcularMediaLaser((*reinterpret_cast< const RoboCompLaser::TLaserData(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpecificWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<GenericWorker::staticMetaObject>(),
    qt_meta_stringdata_SpecificWorker.data,
    qt_meta_data_SpecificWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpecificWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpecificWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpecificWorker.stringdata0))
        return static_cast<void*>(this);
    return GenericWorker::qt_metacast(_clname);
}

int SpecificWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GenericWorker::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
