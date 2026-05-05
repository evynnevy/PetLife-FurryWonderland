#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PetStatus.h"
#include "PetSelectionModel.h"
#include "MusicPlayer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PetStatus>("com.petlife", 1, 0, "PetStatus");

    PetSelectionModel petModel;
    MusicPlayer musicPlayer;

    musicPlayer.setSource("qrc:/audio/bgm.mp3");
    musicPlayer.play();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("petModel", &petModel);
    engine.rootContext()->setContextProperty("musicPlayer", &musicPlayer);
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
