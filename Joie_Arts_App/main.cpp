#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "filters_class.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    app.setWindowIcon(QIcon("C:/Users/madoy/OneDrive/Desktop/JA_Logo.svg"));

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Joy_Animation_App", "Main");

    return app.exec();
}
