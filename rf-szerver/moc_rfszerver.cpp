/****************************************************************************
** Meta object code from reading C++ file 'rfszerver.h'
**
** Created: Tue May 14 19:37:11 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rfszerver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rfszerver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RFSzerver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      32,   10,   10,   10, 0x0a,
      51,   44,   10,   10, 0x0a,
      82,   44,   10,   10, 0x0a,
     121,   44,   10,   10, 0x0a,
     157,   44,   10,   10, 0x0a,
     194,   44,   10,   10, 0x0a,
     237,   44,   10,   10, 0x0a,
     276,   44,   10,   10, 0x0a,
     312,   44,   10,   10, 0x0a,
     352,   44,   10,   10, 0x0a,
     388,   44,   10,   10, 0x0a,
     428,   44,   10,   10, 0x0a,
     462,   44,   10,   10, 0x0a,
     495,   44,   10,   10, 0x0a,
     532,   44,   10,   10, 0x0a,
     566,   44,   10,   10, 0x0a,
     604,   44,   10,   10, 0x0a,
     641,   44,   10,   10, 0x0a,
     675,   44,   10,   10, 0x0a,
     713,   44,   10,   10, 0x0a,
     750,   44,   10,   10, 0x0a,
     794,   44,   10,   10, 0x0a,
     839,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RFSzerver[] = {
    "RFSzerver\0\0incomingConnection()\0"
    "readyRead()\0socket\0handleAuthRequest(QTcpSocket*)\0"
    "handleUtvonallistaRequest(QTcpSocket*)\0"
    "handleBuszlistaRequest(QTcpSocket*)\0"
    "handleSoforlistaRequest(QTcpSocket*)\0"
    "handleUtvonalBuszSoforRequest(QTcpSocket*)\0"
    "handleMegalloListaRequest(QTcpSocket*)\0"
    "handleMegalloUjRequest(QTcpSocket*)\0"
    "handleMegalloTorlesRequest(QTcpSocket*)\0"
    "handleUtvonalUjRequest(QTcpSocket*)\0"
    "handleUtvonalTorlesRequest(QTcpSocket*)\0"
    "handleUtvonalRequest(QTcpSocket*)\0"
    "handleBuszUjRequest(QTcpSocket*)\0"
    "handleBuszTorlesRequest(QTcpSocket*)\0"
    "handleSoforUjRequest(QTcpSocket*)\0"
    "handleSoforTorlesRequest(QTcpSocket*)\0"
    "handleJaratListaRequest(QTcpSocket*)\0"
    "handleJaratUjRequest(QTcpSocket*)\0"
    "handleJaratTorlesRequest(QTcpSocket*)\0"
    "handleBeosztasUjRequest(QTcpSocket*)\0"
    "handleBeosztasNapilistaRequest(QTcpSocket*)\0"
    "handleBeosztasNapitorlesRequest(QTcpSocket*)\0"
    "handleShutdownRequest()\0"
};

void RFSzerver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RFSzerver *_t = static_cast<RFSzerver *>(_o);
        switch (_id) {
        case 0: _t->incomingConnection(); break;
        case 1: _t->readyRead(); break;
        case 2: _t->handleAuthRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 3: _t->handleUtvonallistaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 4: _t->handleBuszlistaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 5: _t->handleSoforlistaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 6: _t->handleUtvonalBuszSoforRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 7: _t->handleMegalloListaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 8: _t->handleMegalloUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 9: _t->handleMegalloTorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 10: _t->handleUtvonalUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 11: _t->handleUtvonalTorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 12: _t->handleUtvonalRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 13: _t->handleBuszUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 14: _t->handleBuszTorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 15: _t->handleSoforUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 16: _t->handleSoforTorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 17: _t->handleJaratListaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 18: _t->handleJaratUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 19: _t->handleJaratTorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 20: _t->handleBeosztasUjRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 21: _t->handleBeosztasNapilistaRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 22: _t->handleBeosztasNapitorlesRequest((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 23: _t->handleShutdownRequest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RFSzerver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RFSzerver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RFSzerver,
      qt_meta_data_RFSzerver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RFSzerver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RFSzerver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RFSzerver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RFSzerver))
        return static_cast<void*>(const_cast< RFSzerver*>(this));
    return QObject::qt_metacast(_clname);
}

int RFSzerver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
