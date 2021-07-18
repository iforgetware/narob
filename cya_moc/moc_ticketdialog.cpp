/****************************************************************************
** Meta object code from reading C++ file 'ticketdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ticketdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ticketdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TicketDialog_t {
    QByteArrayData data[8];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TicketDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TicketDialog_t qt_meta_stringdata_TicketDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TicketDialog"
QT_MOC_LITERAL(1, 13, 24), // "onShowPredictionsClicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 12), // "onDateChange"
QT_MOC_LITERAL(4, 52, 28), // "onTrackTicketsCheckboxChange"
QT_MOC_LITERAL(5, 81, 30), // "onVehicleTicketsCheckboxChange"
QT_MOC_LITERAL(6, 112, 14), // "onFactorChange"
QT_MOC_LITERAL(7, 127, 19) // "onButtonBoxAccepted"

    },
    "TicketDialog\0onShowPredictionsClicked\0"
    "\0onDateChange\0onTrackTicketsCheckboxChange\0"
    "onVehicleTicketsCheckboxChange\0"
    "onFactorChange\0onButtonBoxAccepted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TicketDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TicketDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TicketDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onShowPredictionsClicked(); break;
        case 1: _t->onDateChange(); break;
        case 2: _t->onTrackTicketsCheckboxChange(); break;
        case 3: _t->onVehicleTicketsCheckboxChange(); break;
        case 4: _t->onFactorChange(); break;
        case 5: _t->onButtonBoxAccepted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TicketDialog::staticMetaObject = { {
    &DialogBase::staticMetaObject,
    qt_meta_stringdata_TicketDialog.data,
    qt_meta_data_TicketDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TicketDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TicketDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TicketDialog.stringdata0))
        return static_cast<void*>(this);
    return DialogBase::qt_metacast(_clname);
}

int TicketDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DialogBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
