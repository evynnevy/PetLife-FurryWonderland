#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
public:
    explicit MusicPlayer(QObject *parent = nullptr);

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void setSource(const QString &url);

    bool isPlaying() const;
    qreal volume() const;
    void setVolume(qreal vol);

signals:
    void playingChanged();
    void volumeChanged();

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
};

#endif // MUSICPLAYER_H