#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMediaPlaylist>
#include "video.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);

signals:
    void screenChanged(bool fullScreen);
private slots:
    void openFile();
    void prevClick();
    void nextClick();
    void durationChange(qint64 duration);
    void positionChange(qint64 position);
    void seek(int seconds);

    void videoAvailable(bool available);

private:
     QMediaPlayer *player;

     QPushButton *fullBut;
     Video *videoWin;
     QLabel *play1;     
     QMediaPlaylist *playlistik;     
     QSlider *slider1;    
     qint64 duration;
     QLabel *durLab1;     

     void updateDuration(qint64 currentDur);
};

#endif // PLAYER_H
