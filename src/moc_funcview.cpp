/****************************************************************************
** Meta object code from reading C++ file 'funcview.h'
**
** Created: Fri Apr 29 11:48:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "funcview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'funcview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QwtPlotMagnifierEx[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   35,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QwtPlotMagnifierEx[] = {
    "QwtPlotMagnifierEx\0\0rescaleEvent()\0"
    "factor\0doRescale(double)\0"
};

const QMetaObject QwtPlotMagnifierEx::staticMetaObject = {
    { &QwtPlotMagnifier::staticMetaObject, qt_meta_stringdata_QwtPlotMagnifierEx,
      qt_meta_data_QwtPlotMagnifierEx, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QwtPlotMagnifierEx::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QwtPlotMagnifierEx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QwtPlotMagnifierEx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtPlotMagnifierEx))
        return static_cast<void*>(const_cast< QwtPlotMagnifierEx*>(this));
    return QwtPlotMagnifier::qt_metacast(_clname);
}

int QwtPlotMagnifierEx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlotMagnifier::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rescaleEvent(); break;
        case 1: doRescale((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QwtPlotMagnifierEx::rescaleEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_FuncView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   20,    9,    9, 0x0a,
      45,   20,    9,    9, 0x0a,
      72,   66,   61,    9, 0x0a,
      89,    9,    9,    9, 0x0a,
     104,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FuncView[] = {
    "FuncView\0\0resized()\0i\0changeCoordinates(int)\0"
    "changeGrid(int)\0bool\0gfunc\0plot(GFunction*)\0"
    "updateBounds()\0updateRatio()\0"
};

const QMetaObject FuncView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FuncView,
      qt_meta_data_FuncView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FuncView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FuncView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FuncView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FuncView))
        return static_cast<void*>(const_cast< FuncView*>(this));
    return QWidget::qt_metacast(_clname);
}

int FuncView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: resized(); break;
        case 1: changeCoordinates((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: changeGrid((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { bool _r = plot((*reinterpret_cast< GFunction*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: updateBounds(); break;
        case 5: updateRatio(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FuncView::resized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
