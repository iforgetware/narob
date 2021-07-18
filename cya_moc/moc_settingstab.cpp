/****************************************************************************
** Meta object code from reading C++ file 'settingstab.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settingstab.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingstab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsTab_t {
    QByteArrayData data[18];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsTab_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsTab_t qt_meta_stringdata_SettingsTab = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SettingsTab"
QT_MOC_LITERAL(1, 12, 12), // "updateSplits"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "updateLogbook"
QT_MOC_LITERAL(4, 40, 11), // "testWeather"
QT_MOC_LITERAL(5, 52, 6), // "testTP"
QT_MOC_LITERAL(6, 59, 8), // "testWind"
QT_MOC_LITERAL(7, 68, 10), // "testWeight"
QT_MOC_LITERAL(8, 79, 19), // "onSaveButtonClicked"
QT_MOC_LITERAL(9, 99, 20), // "onClearButtonClicked"
QT_MOC_LITERAL(10, 120, 28), // "onUpdateLogbookButtonClicked"
QT_MOC_LITERAL(11, 149, 28), // "onCleanDatabaseButtonClicked"
QT_MOC_LITERAL(12, 178, 27), // "onUpdateSplitsButtonClicked"
QT_MOC_LITERAL(13, 206, 26), // "onTestWeatherButtonClicked"
QT_MOC_LITERAL(14, 233, 21), // "onTestTPButtonClicked"
QT_MOC_LITERAL(15, 255, 23), // "onTestWindButtonClicked"
QT_MOC_LITERAL(16, 279, 25), // "onTestWeightButtonClicked"
QT_MOC_LITERAL(17, 305, 13) // "displayUpdate"

    },
    "SettingsTab\0updateSplits\0\0updateLogbook\0"
    "testWeather\0testTP\0testWind\0testWeight\0"
    "onSaveButtonClicked\0onClearButtonClicked\0"
    "onUpdateLogbookButtonClicked\0"
    "onCleanDatabaseButtonClicked\0"
    "onUpdateSplitsButtonClicked\0"
    "onTestWeatherButtonClicked\0"
    "onTestTPButtonClicked\0onTestWindButtonClicked\0"
    "onTestWeightButtonClicked\0displayUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsTab[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    0,   98,    2, 0x06 /* Public */,
       7,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingsTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsTab *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSplits(); break;
        case 1: _t->updateLogbook(); break;
        case 2: _t->testWeather(); break;
        case 3: _t->testTP(); break;
        case 4: _t->testWind(); break;
        case 5: _t->testWeight(); break;
        case 6: _t->onSaveButtonClicked(); break;
        case 7: _t->onClearButtonClicked(); break;
        case 8: _t->onUpdateLogbookButtonClicked(); break;
        case 9: _t->onCleanDatabaseButtonClicked(); break;
        case 10: _t->onUpdateSplitsButtonClicked(); break;
        case 11: _t->onTestWeatherButtonClicked(); break;
        case 12: _t->onTestTPButtonClicked(); break;
        case 13: _t->onTestWindButtonClicked(); break;
        case 14: _t->onTestWeightButtonClicked(); break;
        case 15: _t->displayUpdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::updateSplits)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::updateLogbook)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::testWeather)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::testTP)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::testWind)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SettingsTab::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsTab::testWeight)) {
                *result = 5;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SettingsTab::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingsTab.data,
    qt_meta_data_SettingsTab,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingsTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsTab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsTab.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SettingsTab::updateSplits()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsTab::updateLogbook()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SettingsTab::testWeather()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SettingsTab::testTP()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SettingsTab::testWind()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SettingsTab::testWeight()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
