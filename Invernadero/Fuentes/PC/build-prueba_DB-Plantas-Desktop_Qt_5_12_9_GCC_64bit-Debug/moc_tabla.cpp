/****************************************************************************
** Meta object code from reading C++ file 'tabla.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../prueba_DB-Plantas/tabla.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabla.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tabla_t {
    QByteArrayData data[9];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tabla_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tabla_t qt_meta_stringdata_Tabla = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Tabla"
QT_MOC_LITERAL(1, 6, 28), // "on_pushButton_Borrar_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 32), // "on_tableWidget_Datos_cellChanged"
QT_MOC_LITERAL(4, 69, 3), // "row"
QT_MOC_LITERAL(5, 73, 6), // "column"
QT_MOC_LITERAL(6, 80, 41), // "on_tableWidget_Datos_itemSele..."
QT_MOC_LITERAL(7, 122, 29), // "on_pushButton_Agregar_clicked"
QT_MOC_LITERAL(8, 152, 38) // "on_tableWidget_Datos_cellDoub..."

    },
    "Tabla\0on_pushButton_Borrar_clicked\0\0"
    "on_tableWidget_Datos_cellChanged\0row\0"
    "column\0on_tableWidget_Datos_itemSelectionChanged\0"
    "on_pushButton_Agregar_clicked\0"
    "on_tableWidget_Datos_cellDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tabla[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    2,   40,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    2,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,

       0        // eod
};

void Tabla::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tabla *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Borrar_clicked(); break;
        case 1: _t->on_tableWidget_Datos_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_tableWidget_Datos_itemSelectionChanged(); break;
        case 3: _t->on_pushButton_Agregar_clicked(); break;
        case 4: _t->on_tableWidget_Datos_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tabla::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Tabla.data,
    qt_meta_data_Tabla,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tabla::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tabla::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tabla.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Tabla::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
