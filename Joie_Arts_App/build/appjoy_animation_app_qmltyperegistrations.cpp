/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<filters_class.h>)
#  include <filters_class.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_Joy_Animation_App()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<Filters_Class>("Joy_Animation_App", 1);
    QT_WARNING_POP
    qmlRegisterModule("Joy_Animation_App", 1, 0);
}

static const QQmlModuleRegistration joyAnimationAppRegistration("Joy_Animation_App", qml_register_types_Joy_Animation_App);
