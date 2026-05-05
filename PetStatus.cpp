#include "PetStatus.h"
#include <QTimer>
#include <QDebug>

PetStatus::PetStatus(QObject *parent)
    : QObject(parent)
    , m_health(100)     // 初始健康值
    , m_hunger(30)      // 初始饥饿值
    , m_sleepiness(20)  // 初始困倦值
    , m_mood(80)        // 初始心情值
{
    // 每 3 秒自动变化一次（模拟时间流逝）
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        // 饥饿随时间增加
        setHunger(qMin(100, m_hunger + 2));

        // 困倦随时间增加
        setSleepiness(qMin(100, m_sleepiness + 1));

        // 心情会受其他状态影响
        updateMoodBasedOnStatus();

        // 健康会受极值影响
        updateHealthBasedOnStatus();
    });
    timer->start(3000); // 3 秒一次

    // 每 10 秒检查一次是否需要警告
    QTimer *warningTimer = new QTimer(this);
    connect(warningTimer, &QTimer::timeout, this, [this]() {
        if (m_hunger >= 80) {
            qDebug() << "警告：宠物很饿！";
        }
        if (m_sleepiness >= 80) {
            qDebug() << "警告：宠物很困！";
        }
        if (m_health <= 20) {
            qDebug() << "警告：宠物健康不佳！";
        }
    });
    warningTimer->start(10000);
}

// Getter
int PetStatus::health() const { return m_health; }
int PetStatus::hunger() const { return m_hunger; }
int PetStatus::sleepiness() const { return m_sleepiness; }
int PetStatus::mood() const { return m_mood; }

// Setter
void PetStatus::setHealth(int health) {
    health = qBound(0, health, 100);
    if (m_health != health) {
        m_health = health;
        emit healthChanged();
    }
}

void PetStatus::setHunger(int hunger) {
    hunger = qBound(0, hunger, 100);
    if (m_hunger != hunger) {
        m_hunger = hunger;
        emit hungerChanged();
    }
}

void PetStatus::setSleepiness(int sleepiness) {
    sleepiness = qBound(0, sleepiness, 100);
    if (m_sleepiness != sleepiness) {
        m_sleepiness = sleepiness;
        emit sleepinessChanged();
    }
}

void PetStatus::setMood(int mood) {
    mood = qBound(0, mood, 100);
    if (m_mood != mood) {
        m_mood = mood;
        emit moodChanged();
    }
}

// ===== 核心功能 =====

// 喂食：减少饥饿，增加心情
void PetStatus::feed(int amount) {
    int oldHunger = m_hunger;
    setHunger(m_hunger - amount);

    // 计算实际减少的饥饿值
    int actualReduced = oldHunger - m_hunger;

    // 如果确实减少了饥饿，增加心情
    if (actualReduced > 0) {
        setMood(m_mood + 5);
    }

    // 如果喂得太饱（饥饿值过低），略微增加困倦
    if (m_hunger < 20) {
        setSleepiness(m_sleepiness + 3);
    }
}

// 玩耍：增加心情，增加饥饿和困倦
void PetStatus::play(int amount) {
    setMood(m_mood + amount);
    setHunger(m_hunger + 8);      // 玩耍会消耗体力，增加饥饿
    setSleepiness(m_sleepiness + 5); // 玩耍会累，增加困倦
}

// 休息：减少困倦，增加健康
void PetStatus::rest(int amount) {
    int oldSleepiness = m_sleepiness;
    setSleepiness(m_sleepiness - amount);

    // 计算实际减少的困倦值
    int actualReduced = oldSleepiness - m_sleepiness;

    // 如果确实休息了，增加健康
    if (actualReduced > 0) {
        setHealth(m_health + 3);
    }
}

// 治疗：增加健康
void PetStatus::heal(int amount) {
    setHealth(m_health + amount);
}

// 检查状态：返回状态字符串
QString PetStatus::checkStatus() {
    if (m_health < 30) {
        return "宠物生病了，需要治疗！";
    } else if (m_hunger > 80) {
        return "宠物很饿，需要喂食！";
    } else if (m_sleepiness > 80) {
        return "宠物很困，需要休息！";
    } else if (m_mood < 30) {
        return "宠物心情不好，需要玩耍！";
    } else {
        return "宠物状态良好！";
    }
}

// 重置所有状态
void PetStatus::reset() {
    setHealth(100);
    setHunger(30);
    setSleepiness(20);
    setMood(80);
}

// 私有函数：根据其他状态更新心情
void PetStatus::updateMoodBasedOnStatus() {
    int moodChange = 0;

    // 饥饿影响心情
    if (m_hunger > 70) {
        moodChange -= 3;  // 很饿，心情变差
    } else if (m_hunger < 30) {
        moodChange += 1;  // 不饿，心情变好
    }

    // 困倦影响心情
    if (m_sleepiness > 70) {
        moodChange -= 2;  // 很困，心情变差
    } else if (m_sleepiness < 30) {
        moodChange += 1;  // 不困，心情变好
    }

    // 健康影响心情
    if (m_health < 50) {
        moodChange -= 2;  // 健康不佳，心情变差
    } else if (m_health > 80) {
        moodChange += 1;  // 健康良好，心情变好
    }

    if (moodChange != 0) {
        setMood(m_mood + moodChange);
    }
}

// 私有函数：根据状态更新健康
void PetStatus::updateHealthBasedOnStatus() {
    int healthChange = 0;

    // 饥饿严重损害健康
    if (m_hunger > 90) {
        healthChange -= 2;  // 极度饥饿，健康下降
    } else if (m_hunger > 70) {
        healthChange -= 1;  // 饥饿，健康轻微下降
    }

    // 困倦严重损害健康
    if (m_sleepiness > 90) {
        healthChange -= 2;  // 极度困倦，健康下降
    } else if (m_sleepiness > 70) {
        healthChange -= 1;  // 困倦，健康轻微下降
    }

    // 心情很好可以略微恢复健康
    if (m_mood > 80 && m_health < 100) {
        healthChange += 1;  // 心情好，健康恢复
    }

    if (healthChange != 0) {
        setHealth(m_health + healthChange);
    }
}