#include "PetSelectionModel.h"

PetSelectionModel::PetSelectionModel(QObject *parent) : QObject(parent)
{
    // 初始化四种宠物，各有不同初始属性
    // v3.1 新增：宠物性格系统
    //萨摩耶：贪吃 (饥饿速率快，喂食效果好)；布偶猫：休闲（困倦增加更快，休息效果好）；阿比西尼亚猫：活泼（玩耍心情增加多）；金毛：坚强（治疗恢复健康多）
    m_pets = {
        {"samoyed", "萨摩耶", "qrc:/images/Samoyed.png", 100, 30, 20, 80, 1.2, 1.0, 1.2, 1.0, 1.0, 1.0},
        {"ragdoll", "布偶猫", "qrc:/images/Ragdoll.png", 95, 25, 35, 70, 1.0, 1.2, 1.0, 1.0, 1.2, 1.0},
        {"abyssinian", "阿比西尼亚猫", "qrc:/images/Abyssinian.png", 90, 40, 25, 85, 1.0, 1.0, 1.0, 1.3, 1.0, 1.0},
        {"golden", "金毛", "qrc:/images/Golden.png", 100, 20, 15, 90, 1.0, 1.0, 1.0, 1.0, 1.0, 1.2}
    };
    m_currentId = "samoyed";
}

QVariantList PetSelectionModel::pets() const
{
    QVariantList list;
    for (const auto &pet : m_pets) {
        QVariantMap map;
        map["id"] = pet.id;
        map["name"] = pet.name;
        map["imagePath"] = pet.imagePath;
        list.append(map);
    }
    return list;
}

QString PetSelectionModel::currentPetId() const { return m_currentId; }

void PetSelectionModel::setCurrentPetId(const QString &id)
{
    if (m_currentId == id) return;
    m_currentId = id;
    emit currentPetChanged();
}

QString PetSelectionModel::currentPetName() const
{
    for (const auto &pet : m_pets) {
        if (pet.id == m_currentId) return pet.name;
    }
    return "";
}

QString PetSelectionModel::currentPetImage() const
{
    for (const auto &pet : m_pets) {
        if (pet.id == m_currentId) return pet.imagePath;
    }
    return "";
}

void PetSelectionModel::selectPet(const QString &id)
{
    setCurrentPetId(id);
}

QString PetSelectionModel::getPetImage(const QString &id) const
{
    for (const auto &pet : m_pets) {
        if (pet.id == id) return pet.imagePath;
    }
    return "";
}

int PetSelectionModel::getPetDefaultHealth(const QString &id) const
{
    for (const auto &pet : m_pets) {
        if (pet.id == id) return pet.defaultHealth;
    }
    return 100;
}

int PetSelectionModel::getPetDefaultHunger(const QString &id) const
{
    for (const auto &pet : m_pets) {
        if (pet.id == id) return pet.defaultHunger;
    }
    return 30;
}

int PetSelectionModel::getPetDefaultSleepiness(const QString &id) const
{
    for (const auto &pet : m_pets) {
        if (pet.id == id) return pet.defaultSleepiness;
    }
    return 20;
}

int PetSelectionModel::getPetDefaultMood(const QString &id) const
{
    for (const auto &pet : m_pets) {
        if (pet.id == id) return pet.defaultMood;
    }
    return 80;
}

// v3.1 新增：宠物性格系统
double PetSelectionModel::getHungryRate(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.hungryRate;
    return 1.0;
}

double PetSelectionModel::getSleepyRate(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.sleepyRate;
    return 1.0;
}

double PetSelectionModel::getFeedEffect(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.feedEffect;
    return 1.0;
}

double PetSelectionModel::getPlayEffect(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.playEffect;
    return 1.0;
}

double PetSelectionModel::getRestEffect(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.restEffect;
    return 1.0;
}

double PetSelectionModel::getHealEffect(const QString &id) const
{
    for (const auto &pet : m_pets)
        if (pet.id == id) return pet.healEffect;
    return 1.0;
}
