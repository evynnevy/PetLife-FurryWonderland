#ifndef PETSTATUS_H
#define PETSTATUS_H

#include <QObject>
#include <QString>

class PetStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int health READ health WRITE setHealth NOTIFY healthChanged)
    Q_PROPERTY(int hunger READ hunger WRITE setHunger NOTIFY hungerChanged)
    Q_PROPERTY(int sleepiness READ sleepiness WRITE setSleepiness NOTIFY sleepinessChanged)
    Q_PROPERTY(int mood READ mood WRITE setMood NOTIFY moodChanged)

public:
    explicit PetStatus(QObject *parent = nullptr);

    // Getter
    int health() const;
    int hunger() const;
    int sleepiness() const;
    int mood() const;

    // Setter
    void setHealth(int health);
    void setHunger(int hunger);
    void setSleepiness(int sleepiness);
    void setMood(int mood);

    // 功能方法
    Q_INVOKABLE void feed(int amount = 20);       // 喂食
    Q_INVOKABLE void play(int amount = 10);       // 玩耍
    Q_INVOKABLE void rest(int amount = 15);       // 休息
    Q_INVOKABLE void heal(int amount = 25);       // 治疗
    Q_INVOKABLE QString checkStatus();            // 检查状态
    Q_INVOKABLE void reset();                     // 重置所有状态

signals:
    void healthChanged();
    void hungerChanged();
    void sleepinessChanged();
    void moodChanged();
    void statusWarning(QString message);  // 状态警告信号

private:
    void updateMoodBasedOnStatus();  // 根据其他状态更新心情
    void updateHealthBasedOnStatus(); // 根据状态更新健康

    int m_health;      // 健康值 0-100
    int m_hunger;      // 饥饿值 0-100
    int m_sleepiness;  // 困倦值 0-100
    int m_mood;        // 心情值 0-100
};

#endif // PETSTATUS_H