#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "PetStatus.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PetStatus>("com.petlife", 1, 0, "PetStatus");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}