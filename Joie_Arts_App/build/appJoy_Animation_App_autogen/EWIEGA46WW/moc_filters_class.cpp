/****************************************************************************
** Meta object code from reading C++ file 'filters_class.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../filters_class.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filters_class.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13Filters_ClassE_t {};
} // unnamed namespace

template <> constexpr inline auto Filters_Class::qt_create_metaobjectdata<qt_meta_tag_ZN13Filters_ClassE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Filters_Class",
        "QML.Element",
        "auto",
        "imageSourceChanged",
        "",
        "loadImage",
        "path",
        "loadSecondImage",
        "saveImage",
        "applyGrayscale",
        "applyBnW",
        "applyInvert",
        "applyFlipFilter",
        "x",
        "applyDarkenOrLighten",
        "applyRotatefilter",
        "applyResizeFilter",
        "applyInfraRedFilter",
        "applyCropFilter",
        "applyEdgeDetetction",
        "applyBlur",
        "applyTVstatic",
        "applyOilFilter",
        "applyNaturalSunlight",
        "applyMergeFilter",
        "undo",
        "redo",
        "resize",
        "y",
        "crop",
        "w",
        "h",
        "applyInfraRed",
        "applyMidNight",
        "skewImage",
        "applyGamma",
        "applyContrast",
        "applyVignette",
        "applyNoise",
        "applyFishEye",
        "applyToonyEffect",
        "applyEmboss",
        "applyFrame",
        "frameType",
        "thickness",
        "inner",
        "gap",
        "R",
        "G",
        "B",
        "applyHue",
        "z",
        "applyGlitch",
        "applyPixelArt",
        "sharpen",
        "applyNightyeffect",
        "reset",
        "imageSource"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'imageSourceChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadImage'
        QtMocHelpers::MethodData<void(const QString &)>(5, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Method 'loadSecondImage'
        QtMocHelpers::MethodData<void(const QString &)>(7, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Method 'saveImage'
        QtMocHelpers::MethodData<void(const QString &)>(8, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Method 'applyGrayscale'
        QtMocHelpers::MethodData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyBnW'
        QtMocHelpers::MethodData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyInvert'
        QtMocHelpers::MethodData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyFlipFilter'
        QtMocHelpers::MethodData<void(int)>(12, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'applyDarkenOrLighten'
        QtMocHelpers::MethodData<void(float)>(14, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyRotatefilter'
        QtMocHelpers::MethodData<void(int)>(15, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'applyResizeFilter'
        QtMocHelpers::MethodData<void()>(16, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyInfraRedFilter'
        QtMocHelpers::MethodData<void()>(17, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyCropFilter'
        QtMocHelpers::MethodData<void()>(18, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyEdgeDetetction'
        QtMocHelpers::MethodData<void()>(19, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyBlur'
        QtMocHelpers::MethodData<void()>(20, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyTVstatic'
        QtMocHelpers::MethodData<void()>(21, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyOilFilter'
        QtMocHelpers::MethodData<void()>(22, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyNaturalSunlight'
        QtMocHelpers::MethodData<void()>(23, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyMergeFilter'
        QtMocHelpers::MethodData<void(int)>(24, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'undo'
        QtMocHelpers::MethodData<void()>(25, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'redo'
        QtMocHelpers::MethodData<void()>(26, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'resize'
        QtMocHelpers::MethodData<void(int, int)>(27, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 28 },
        }}),
        // Method 'crop'
        QtMocHelpers::MethodData<void(int, int, int, int)>(29, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 28 }, { QMetaType::Int, 30 }, { QMetaType::Int, 31 },
        }}),
        // Method 'applyInfraRed'
        QtMocHelpers::MethodData<void()>(32, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyMidNight'
        QtMocHelpers::MethodData<void()>(33, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'skewImage'
        QtMocHelpers::MethodData<void(float)>(34, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyGamma'
        QtMocHelpers::MethodData<void(float)>(35, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyContrast'
        QtMocHelpers::MethodData<void(float)>(36, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyVignette'
        QtMocHelpers::MethodData<void(float)>(37, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyNoise'
        QtMocHelpers::MethodData<void(float)>(38, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 },
        }}),
        // Method 'applyFishEye'
        QtMocHelpers::MethodData<void()>(39, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyToonyEffect'
        QtMocHelpers::MethodData<void()>(40, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyEmboss'
        QtMocHelpers::MethodData<void()>(41, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyFrame'
        QtMocHelpers::MethodData<void(int, int, int, int, unsigned int, unsigned int, unsigned int)>(42, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 43 }, { QMetaType::Int, 44 }, { QMetaType::Int, 45 }, { QMetaType::Int, 46 },
            { QMetaType::UInt, 47 }, { QMetaType::UInt, 48 }, { QMetaType::UInt, 49 },
        }}),
        // Method 'applyHue'
        QtMocHelpers::MethodData<void(float, float, float)>(50, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 13 }, { QMetaType::Float, 28 }, { QMetaType::Float, 51 },
        }}),
        // Method 'applyGlitch'
        QtMocHelpers::MethodData<void()>(52, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyPixelArt'
        QtMocHelpers::MethodData<void()>(53, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'sharpen'
        QtMocHelpers::MethodData<void()>(54, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'applyNightyeffect'
        QtMocHelpers::MethodData<void()>(55, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'reset'
        QtMocHelpers::MethodData<void()>(56, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'imageSource'
        QtMocHelpers::PropertyData<QUrl>(57, QMetaType::QUrl, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<Filters_Class, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Filters_Class::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13Filters_ClassE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13Filters_ClassE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13Filters_ClassE_t>.metaTypes,
    nullptr
} };

void Filters_Class::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Filters_Class *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->imageSourceChanged(); break;
        case 1: _t->loadImage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->loadSecondImage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->saveImage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->applyGrayscale(); break;
        case 5: _t->applyBnW(); break;
        case 6: _t->applyInvert(); break;
        case 7: _t->applyFlipFilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->applyDarkenOrLighten((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 9: _t->applyRotatefilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->applyResizeFilter(); break;
        case 11: _t->applyInfraRedFilter(); break;
        case 12: _t->applyCropFilter(); break;
        case 13: _t->applyEdgeDetetction(); break;
        case 14: _t->applyBlur(); break;
        case 15: _t->applyTVstatic(); break;
        case 16: _t->applyOilFilter(); break;
        case 17: _t->applyNaturalSunlight(); break;
        case 18: _t->applyMergeFilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->undo(); break;
        case 20: _t->redo(); break;
        case 21: _t->resize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 22: _t->crop((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 23: _t->applyInfraRed(); break;
        case 24: _t->applyMidNight(); break;
        case 25: _t->skewImage((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 26: _t->applyGamma((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 27: _t->applyContrast((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 28: _t->applyVignette((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 29: _t->applyNoise((*reinterpret_cast< std::add_pointer_t<float>>(_a[1]))); break;
        case 30: _t->applyFishEye(); break;
        case 31: _t->applyToonyEffect(); break;
        case 32: _t->applyEmboss(); break;
        case 33: _t->applyFrame((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<uint>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<uint>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<uint>>(_a[7]))); break;
        case 34: _t->applyHue((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3]))); break;
        case 35: _t->applyGlitch(); break;
        case 36: _t->applyPixelArt(); break;
        case 37: _t->sharpen(); break;
        case 38: _t->applyNightyeffect(); break;
        case 39: _t->reset(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Filters_Class::*)()>(_a, &Filters_Class::imageSourceChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QUrl*>(_v) = _t->imageSource(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setImageSource(*reinterpret_cast<QUrl*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Filters_Class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Filters_Class::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13Filters_ClassE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Filters_Class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 40;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Filters_Class::imageSourceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
