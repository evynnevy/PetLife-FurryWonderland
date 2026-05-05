#include "PetSelectionModel.h"

PetSelectionModel::PetSelectionModel(QObject *parent) : QObject(parent)
{
    // 初始化四种宠物，各有不同初始属性
    m_pets = {
        {"samoyed", "萨摩耶", "qrc:/images/Samoyed.png", 100, 30, 20, 80},
        {"ragdoll", "布偶猫", "qrc:/images/Ragdoll.png", 95, 25, 35, 70},
        {"abyssinian", "阿比西尼亚猫", "qrc:/images/Abyssinian.png", 90, 40, 25, 85},
        {"golden", "金毛", "qrc:/images/Golden.png", 100, 20, 15, 90}
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