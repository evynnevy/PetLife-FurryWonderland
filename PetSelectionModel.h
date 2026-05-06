#ifndef PETSELECTIONMODEL_H
#define PETSELECTIONMODEL_H

#include <QObject>
#include <QVariantList>
#include <QStringList>

struct PetInfo {
    QString id;
    QString name;
    QString imagePath;
    int defaultHealth;
    int defaultHunger;
    int defaultSleepiness;
    int defaultMood;

    // v3.1:新增宠物性格系统
    double hungryRate;      // 饥饿变化速率乘数
    double sleepyRate;      // 困倦变化速率乘数
    double feedEffect;      // 喂食效果乘数
    double playEffect;      // 玩耍效果乘数
    double restEffect;      // 休息效果乘数
    double healEffect;      // 治疗效果乘数
};

class PetSelectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList pets READ pets NOTIFY petsChanged)
    Q_PROPERTY(QString currentPetId READ currentPetId WRITE setCurrentPetId NOTIFY currentPetChanged)
    Q_PROPERTY(QString currentPetName READ currentPetName NOTIFY currentPetChanged)
    Q_PROPERTY(QString currentPetImage READ currentPetImage NOTIFY currentPetChanged)

public:
    explicit PetSelectionModel(QObject *parent = nullptr);

    QVariantList pets() const;
    QString currentPetId() const;
    void setCurrentPetId(const QString &id);
    QString currentPetName() const;
    QString currentPetImage() const;

    // 供 QML 调用
    Q_INVOKABLE void selectPet(const QString &id);
    Q_INVOKABLE QString getPetImage(const QString &id) const;
    Q_INVOKABLE int getPetDefaultHealth(const QString &id) const;
    Q_INVOKABLE int getPetDefaultHunger(const QString &id) const;
    Q_INVOKABLE int getPetDefaultSleepiness(const QString &id) const;
    Q_INVOKABLE int getPetDefaultMood(const QString &id) const;

    // v3.1新增：性格系数获取
    Q_INVOKABLE double getHungryRate(const QString &id) const;
    Q_INVOKABLE double getSleepyRate(const QString &id) const;
    Q_INVOKABLE double getFeedEffect(const QString &id) const;
    Q_INVOKABLE double getPlayEffect(const QString &id) const;
    Q_INVOKABLE double getRestEffect(const QString &id) const;
    Q_INVOKABLE double getHealEffect(const QString &id) const;

signals:
    void petsChanged();
    void currentPetChanged();

private:
    QList<PetInfo> m_pets;
    QString m_currentId;
};

#endif // PETSELECTIONMODEL_H
