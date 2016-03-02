#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QObject>
#include <QVector>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "video.h"

class MultiPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MultiPlayer(QObject *parent = 0);
    //Добавление/удаление
    int addStream();//Добавить поток (возвращаем номер добавленного потока)
    bool delStream(int number);//Удалить поток (если был) вернуть true в случае успеха
    //
    bool attachVideoWidget(int number, Video &widget);
    bool detachVideoWidget(int number);
    //
    bool setVolume(int number, int volume);
    //
    int streamCount();
    //
    bool setMediaURI(int number, QString uri);//Открыть файл/URL для потока

signals:


public slots:
    //Управление потоками
    void pause(int number);
    void play(int number);

private:
    QVector<QMediaPlayer *> players;
    QVector<QMediaPlaylist *> playlists;
};


#endif // MULTIPLAYER_H
