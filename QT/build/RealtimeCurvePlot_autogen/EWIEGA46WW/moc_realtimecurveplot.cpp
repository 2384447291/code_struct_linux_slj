/****************************************************************************
** Meta object code from reading C++ file 'realtimecurveplot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../realtimecurveplot.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'realtimecurveplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RealtimeCurvePlot_t {
    const uint offsetsAndSize[24];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_RealtimeCurvePlot_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_RealtimeCurvePlot_t qt_meta_stringdata_RealtimeCurvePlot = {
    {
QT_MOC_LITERAL(0, 17), // "RealtimeCurvePlot"
QT_MOC_LITERAL(18, 12), // "refreshCurve"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 13), // "onLegendClick"
QT_MOC_LITERAL(46, 10), // "QCPLegend*"
QT_MOC_LITERAL(57, 6), // "legend"
QT_MOC_LITERAL(64, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(87, 4), // "item"
QT_MOC_LITERAL(92, 12), // "QMouseEvent*"
QT_MOC_LITERAL(105, 5), // "event"
QT_MOC_LITERAL(111, 22), // "onDisplayLengthChanged"
QT_MOC_LITERAL(134, 5) // "index"

    },
    "RealtimeCurvePlot\0refreshCurve\0\0"
    "onLegendClick\0QCPLegend*\0legend\0"
    "QCPAbstractLegendItem*\0item\0QMouseEvent*\0"
    "event\0onDisplayLengthChanged\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealtimeCurvePlot[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    3,   33,    2, 0x08,    2 /* Private */,
      10,    1,   40,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 8,    5,    7,    9,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void RealtimeCurvePlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RealtimeCurvePlot *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->refreshCurve(); break;
        case 1: _t->onLegendClick((*reinterpret_cast< std::add_pointer_t<QCPLegend*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAbstractLegendItem*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 2: _t->onDisplayLengthChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLegend* >(); break;
            }
            break;
        }
    }
}

const QMetaObject RealtimeCurvePlot::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_RealtimeCurvePlot.offsetsAndSize,
    qt_meta_data_RealtimeCurvePlot,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_RealtimeCurvePlot_t
, QtPrivate::TypeAndForceComplete<RealtimeCurvePlot, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QCPLegend *, std::false_type>, QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem *, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *RealtimeCurvePlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealtimeCurvePlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RealtimeCurvePlot.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RealtimeCurvePlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
