#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PetStatus.h"
#include "PetSelectionModel.h"
#include "MusicPlayer.h"
#include "SaveManager.h"
#include "SoundEffectPlayer.h"

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);

    qmlRegisterType<PetStatus>("com.petlife", 1, 0, "PetStatus");

    //v2.0 新增：宠物选择
    PetSelectionModel petModel;

    //v2.0 新增：全局bgm
    MusicPlayer musicPlayer;
    musicPlayer.setSource("qrc:/audio/bgm.mp3");
    musicPlayer.play();

    //v3.0 新增：存档读档系统
    PetStatus globalPetStatus;
    SaveManager saveManager(&globalPetStatus, &petModel, &musicPlayer);

    // v3.2 新增：猫叫狗叫音效
    SoundEffectPlayer soundEffectPlayer;
    globalPetStatus.setSoundEffectPlayer(&soundEffectPlayer);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("petModel", &petModel);
    engine.rootContext()->setContextProperty("musicPlayer", &musicPlayer);
    engine.rootContext()->setContextProperty("petStatus", &globalPetStatus);
    engine.rootContext()->setContextProperty("saveManager", &saveManager);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
