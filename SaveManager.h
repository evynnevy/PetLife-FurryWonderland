#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>
#include <QDateTime>

class PetStatus;
class PetSelectionModel;
class MusicPlayer;

class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(PetStatus *petStatus,
                         PetSelectionModel *petModel,
                         MusicPlayer *musicPlayer,
                         QObject *parent = nullptr);

    Q_INVOKABLE void saveGame();      // 保存
    Q_INVOKABLE void loadGame();      // 加载
    Q_INVOKABLE bool hasSaveFile();   // 是否有存档
    Q_INVOKABLE void resetGame();     // 重置为默认状态

    Q_INVOKABLE QString lastSaveTime() const; // 上次保存时间

private:
    PetStatus *m_petStatus;
    PetSelectionModel *m_petModel;
    MusicPlayer *m_musicPlayer;
};

#endif // SAVEMANAGER_H