#ifndef SOUNDEFFECTPLAYER_H
#define SOUNDEFFECTPLAYER_H

#include <QObject>
#include <QSoundEffect>

class SoundEffectPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SoundEffectPlayer(QObject *parent = nullptr);

    Q_INVOKABLE void playMeow();   // 猫叫
    Q_INVOKABLE void playWoof();   // 狗叫

private:
    QSoundEffect *m_meowEffect;
    QSoundEffect *m_woofEffect;
};

#endif // SOUNDEFFECTPLAYER_H