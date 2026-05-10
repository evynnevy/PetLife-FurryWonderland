#include "SaveManager.h"
#include "PetStatus.h"
#include "PetSelectionModel.h"
#include "MusicPlayer.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

SaveManager::SaveManager(PetStatus *petStatus,
                         PetSelectionModel *petModel,
                         MusicPlayer *musicPlayer,
                         QObject *parent)
    : QObject(parent), m_petStatus(petStatus), m_petModel(petModel), m_musicPlayer(musicPlayer)
{
}

static QString getSaveFilePath()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    return dir + "/savegame.json";
}

void SaveManager::saveGame()
{
    QString filePath = getSaveFilePath();
    QDir dir = QFileInfo(filePath).dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "无法创建存档目录：" << dir.path();
            return;
        }
    }

    QJsonObject json;
    json["currentPetId"] = m_petModel->currentPetId();
    json["health"] = m_petStatus->health();
    json["hunger"] = m_petStatus->hunger();
    json["sleepiness"] = m_petStatus->sleepiness();
    json["mood"] = m_petStatus->mood();
    json["volume"] = m_musicPlayer->volume();
    json["lastSaveTime"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法保存游戏：" << file.errorString();
        return;
    }
    file.write(QJsonDocument(json).toJson());
    qDebug() << "游戏已保存到：" << filePath;
}

void SaveManager::loadGame()
{
    QString filePath = getSaveFilePath();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "没有存档文件：" << filePath;
        return;
    }
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "存档文件损坏";
        return;
    }
    QJsonObject json = doc.object();

    m_petModel->setCurrentPetId(json["currentPetId"].toString("samoyed"));
    m_petStatus->setHealth(json["health"].toInt(100));
    m_petStatus->setHunger(json["hunger"].toInt(30));
    m_petStatus->setSleepiness(json["sleepiness"].toInt(20));
    m_petStatus->setMood(json["mood"].toInt(80));
    m_musicPlayer->setVolume(json["volume"].toDouble(0.5));

    qDebug() << "游戏已加载，上次保存时间：" << json["lastSaveTime"].toString();
}

bool SaveManager::hasSaveFile()
{
    return QFile::exists(getSaveFilePath());
}

void SaveManager::resetGame()
{
    m_petModel->setCurrentPetId("samoyed");
    m_petStatus->reset();
    m_musicPlayer->setVolume(0.5);
    qDebug() << "游戏已重置";
}

QString SaveManager::lastSaveTime() const
{
    QFile file(getSaveFilePath());
    if (!file.open(QIODevice::ReadOnly))
        return QString();
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return doc.object()["lastSaveTime"].toString();
}