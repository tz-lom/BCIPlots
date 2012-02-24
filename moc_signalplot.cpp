/****************************************************************************
** Meta object code from reading C++ file 'signalplot.h'
**
** Created: Thu Feb 23 17:01:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "signalplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signalplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SignalPlot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,
      43,   38,   11,   11, 0x0a,
      71,   61,   11,   11, 0x0a,
      99,   95,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SignalPlot[] = {
    "SignalPlot\0\0channels\0setChannels(int)\0"
    "freq\0setFrequency(int)\0data,size\0"
    "addData(const int*,int)\0amp\0"
    "setAmplification(double)\0"
};

void SignalPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SignalPlot *_t = static_cast<SignalPlot *>(_o);
        switch (_id) {
        case 0: _t->setChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setFrequency((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addData((*reinterpret_cast< const int*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->setAmplification((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SignalPlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SignalPlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SignalPlot,
      qt_meta_data_SignalPlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SignalPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SignalPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SignalPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SignalPlot))
        return static_cast<void*>(const_cast< SignalPlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int SignalPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
