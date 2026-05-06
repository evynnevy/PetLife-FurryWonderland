#include "PetStatus.h"
#include <QTimer>
#include <QDebug>
#include "SoundEffectPlayer.h"

    //判断是猫是狗
    static bool isCat(const QString &type){
        return type == "ragdoll" || type == "abyssinian";
    }

    static bool isDog(const QString &type){
        return type == "samoyed" || type == "golden";
    }

PetStatus::PetStatus(QObject *parent)
    : QObject(parent)
    , m_health(100)     // 初始健康值
    , m_hunger(30)      // 初始饥饿值
    , m_sleepiness(20)  // 初始困倦值
    , m_mood(80)        // 初始心情值

    // v3.1 新增：宠物性格系统
    , m_hungryRate(1.0)
    , m_sleepyRate(1.0)
    , m_feedEffect(1.0)
    , m_playEffect(1.0)
    , m_restEffect(1.0)
    , m_healEffect(1.0)

    // v3.1 新增：互动疲劳与冷却系统
    , m_fatigueCount(0)
{
    m_lastOperationTime = QDateTime::currentDateTime();

    // 每 3 秒自动变化一次
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        int hungerDelta = static_cast<int>(2 * m_hungryRate);
        int sleepinessDelta = static_cast<int>(1 * m_sleepyRate);
        setHunger(qMin(100, m_hunger + hungerDelta));
        setSleepiness(qMin(100, m_sleepiness + sleepinessDelta));
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

    // v3.2 新增：猫叫狗叫音效
    void PetStatus::setSoundEffectPlayer(SoundEffectPlayer *player){
        m_soundPlayer = player;
    }

    void PetStatus::setPetType(const QString &type){
        m_petType = type;
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

    // v3.1 新增：宠物性格系统
    void PetStatus::setPersonality(double hungryRate, double sleepyRate,
                                   double feedEffect, double playEffect,
                                   double restEffect, double healEffect)
    {
        m_hungryRate = hungryRate;
        m_sleepyRate = sleepyRate;
        m_feedEffect = feedEffect;
        m_playEffect = playEffect;
        m_restEffect = restEffect;
        m_healEffect = healEffect;
        qDebug() << "性格系数已更新: hungryRate=" << m_hungryRate << " feedEffect=" << m_feedEffect;
    }

    // v3.1 新增：互动疲劳与冷却系统
    double PetStatus::getCurrentEffectFactor() const{
        // 如果不操作，返回满系数 1.0
        if (m_fatigueCount == 0) return 1.0;

        // 计算距离上一次操作的时间差
        qint64 secondsSinceLast = m_lastOperationTime.secsTo(QDateTime::currentDateTime());
        // 如果超过 5 秒，疲劳重置，系数恢复为 1.0
        if (secondsSinceLast >= 5) return 1.0;

        // 否则根据连续操作次数递减：连续第 2 次 0.9，第 3 次 0.8，最多递减到 0.5
        double factor = 1.0 - (m_fatigueCount - 1) * 0.1;
        return qBound(0.5, factor, 1.0);
    }

    void PetStatus::recordOperation(){
        QDateTime now = QDateTime::currentDateTime();
        if (m_fatigueCount == 0 || m_lastOperationTime.secsTo(now) >= 5) {
            // 如果冷却已过，重置计数
            m_fatigueCount = 1;
        } else {
            // 连续操作，增加计数
            m_fatigueCount++;
        }
        m_lastOperationTime = now;
    }

    void PetStatus::feed(int amount){
        // v3.2 新增：猫叫狗叫音效
        if (m_soundPlayer) {
            if (isCat(m_petType))
                m_soundPlayer->playMeow();
            else if (isDog(m_petType))
                m_soundPlayer->playWoof();
        }

        recordOperation();
        double factor = getCurrentEffectFactor();
        int actualAmount = static_cast<int>(amount * factor);
        int oldHunger = m_hunger;
        setHunger(m_hunger - actualAmount);
        int actualReduced = oldHunger - m_hunger;
        if (actualReduced > 0) {
            setMood(m_mood + static_cast<int>(5 * factor));
        }
        if (m_hunger < 20) {
            setSleepiness(m_sleepiness + static_cast<int>(3 * factor));
        }
    }

    void PetStatus::play(int amount){
        // v3.2 新增：猫叫狗叫音效
        if (m_soundPlayer) {
            if (isCat(m_petType))
                m_soundPlayer->playMeow();
            else if (isDog(m_petType))
                m_soundPlayer->playWoof();
        }

        recordOperation();
        double factor = getCurrentEffectFactor();
        int actualAmount = static_cast<int>(amount * factor);
        setMood(m_mood + actualAmount);
        setHunger(m_hunger + static_cast<int>(8 * factor));
        setSleepiness(m_sleepiness + static_cast<int>(5 * factor));
    }

    void PetStatus::rest(int amount){
        // v3.2 新增：猫叫狗叫音效
        if (m_soundPlayer) {
            if (isCat(m_petType))
                m_soundPlayer->playMeow();
            else if (isDog(m_petType))
                m_soundPlayer->playWoof();
        }

        recordOperation();
        double factor = getCurrentEffectFactor();
        int actualAmount = static_cast<int>(amount * factor);
        int oldSleepiness = m_sleepiness;
        setSleepiness(m_sleepiness - actualAmount);
        int actualReduced = oldSleepiness - m_sleepiness;
        if (actualReduced > 0) {
            setHealth(m_health + static_cast<int>(3 * factor));
        }
    }

    void PetStatus::heal(int amount){
        // v3.2 新增：猫叫狗叫音效
        if (m_soundPlayer) {
            if (isCat(m_petType))
                m_soundPlayer->playMeow();
            else if (isDog(m_petType))
                m_soundPlayer->playWoof();
        }

        recordOperation();
        double factor = getCurrentEffectFactor();
        int actualAmount = static_cast<int>(amount * factor);
        setHealth(m_health + actualAmount);
    }

    QString PetStatus::checkStatus(){
        if (m_health < 30) return "宠物生病了，需要治疗！";
        if (m_hunger > 80) return "宠物很饿，需要喂食！";
        if (m_sleepiness > 80) return "宠物很困，需要休息！";
        if (m_mood < 30) return "宠物心情不好，需要玩耍！";
        return "宠物状态良好！";
    }

    void PetStatus::reset(){
        setHealth(100);
        setHunger(30);
        setSleepiness(20);
        setMood(80);
        m_fatigueCount = 0;
        m_lastOperationTime = QDateTime::currentDateTime();
    }

    void PetStatus::updateMoodBasedOnStatus(){
        int moodChange = 0;
        if (m_hunger > 70) moodChange -= 3;  //太饿导致心情变差
        else if (m_hunger < 30) moodChange += 1;
        if (m_sleepiness > 70) moodChange -= 2;  //太困导致心情变差
        else if (m_sleepiness < 30) moodChange += 1;
        if (m_health < 50) moodChange -= 2;  //健康状态差导致心情变差
        else if (m_health > 80) moodChange += 1;
        if (moodChange != 0) setMood(m_mood + moodChange);
    }

    void PetStatus::updateHealthBasedOnStatus(){
        int healthChange = 0;
        if (m_hunger > 90) healthChange -= 2;  //太饿导致健康状态下降
        else if (m_hunger > 70) healthChange -= 1;
        if (m_sleepiness > 90) healthChange -= 2;  //太太困导致健康状态下降
        else if (m_sleepiness > 70) healthChange -= 1;  //太困导致健康状态下降
        if (m_mood > 80 && m_health < 100) healthChange += 1;  //心情很好，可以恢复健康
        if (healthChange != 0) setHealth(m_health + healthChange);
    }
