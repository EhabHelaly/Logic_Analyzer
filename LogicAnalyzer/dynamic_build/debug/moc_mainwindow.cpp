/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "on_plot_mousePress"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 44, 5), // "event"
QT_MOC_LITERAL(5, 50, 24), // "on_pushB_connect_pressed"
QT_MOC_LITERAL(6, 75, 24), // "on_pushB_capture_pressed"
QT_MOC_LITERAL(7, 100, 24), // "on_pushB_analyze_pressed"
QT_MOC_LITERAL(8, 125, 34), // "on_pop_clkFreq_currentIndexCh..."
QT_MOC_LITERAL(9, 160, 5), // "index"
QT_MOC_LITERAL(10, 166, 25), // "on_checkB_bg_stateChanged"
QT_MOC_LITERAL(11, 192, 5), // "state"
QT_MOC_LITERAL(12, 198, 26), // "on_checkB_adc_stateChanged"
QT_MOC_LITERAL(13, 225, 30), // "on_checkB_schmitt_stateChanged"
QT_MOC_LITERAL(14, 256, 31), // "on_spin_schmittLow_valueChanged"
QT_MOC_LITERAL(15, 288, 5), // "value"
QT_MOC_LITERAL(16, 294, 32) // "on_spin_schmittHigh_valueChanged"

    },
    "MainWindow\0on_plot_mousePress\0\0"
    "QMouseEvent*\0event\0on_pushB_connect_pressed\0"
    "on_pushB_capture_pressed\0"
    "on_pushB_analyze_pressed\0"
    "on_pop_clkFreq_currentIndexChanged\0"
    "index\0on_checkB_bg_stateChanged\0state\0"
    "on_checkB_adc_stateChanged\0"
    "on_checkB_schmitt_stateChanged\0"
    "on_spin_schmittLow_valueChanged\0value\0"
    "on_spin_schmittHigh_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      14,    1,   82,    2, 0x08 /* Private */,
      16,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   15,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_plot_mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->on_pushB_connect_pressed(); break;
        case 2: _t->on_pushB_capture_pressed(); break;
        case 3: _t->on_pushB_analyze_pressed(); break;
        case 4: _t->on_pop_clkFreq_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkB_bg_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_checkB_adc_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_checkB_schmitt_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_spin_schmittLow_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_spin_schmittHigh_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
