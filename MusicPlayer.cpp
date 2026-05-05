#include "MusicPlayer.h"
#include <QUrl>

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
{
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5);
    m_player->setLoops(QMediaPlayer::Infinite); // 循环播放
}

void MusicPlayer::play() { m_player->play(); }
void MusicPlayer::pause() { m_player->pause(); }
void MusicPlayer::setSource(const QString &url)
{
    m_player->setSource(QUrl(url));
}
bool MusicPlayer::isPlaying() const { return m_player->playbackState() == QMediaPlayer::PlayingState; }
qreal MusicPlayer::volume() const { return m_audioOutput->volume(); }
void MusicPlayer::setVolume(qreal vol)
{
    if (vol < 0.0) vol = 0.0;
    if (vol > 1.0) vol = 1.0;
    m_audioOutput->setVolume(vol);
    emit volumeChanged();
}