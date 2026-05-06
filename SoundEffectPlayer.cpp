#include "SoundEffectPlayer.h"
#include <QUrl>
#include <QDebug>

SoundEffectPlayer::SoundEffectPlayer(QObject *parent) : QObject(parent)
{
    m_meowEffect = new QSoundEffect(this);
    m_meowEffect->setSource(QUrl("qrc:/audio/cat_meow.wav"));
    m_meowEffect->setVolume(1.0f);
    qDebug() << "meow loaded:" << m_meowEffect->isLoaded();   // 调试输出

    m_woofEffect = new QSoundEffect(this);
    m_woofEffect->setSource(QUrl("qrc:/audio/dog_woof.wav"));
    m_woofEffect->setVolume(0.8f);
    qDebug() << "woof loaded:" << m_woofEffect->isLoaded();   // 调试输出
}

void SoundEffectPlayer::playMeow()
{
    if (m_meowEffect->isLoaded())
        m_meowEffect->play();
}

void SoundEffectPlayer::playWoof()
{
    if (m_woofEffect->isLoaded())
        m_woofEffect->play();
}