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

signals:
    void petsChanged();
    void currentPetChanged();

private:
    QList<PetInfo> m_pets;
    QString m_currentId;
};

#endif // PETSELECTIONMODEL_H