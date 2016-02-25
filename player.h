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
    void openFile2();
    void prevClick();
    void nextClick();
    void prevClick2();
    void nextClick2();
    void durationChange(qint64 duration);
    void positionChange(qint64 position);
    void seek(int seconds);
    void durationChange2(qint64 duration);
    void positionChange2(qint64 position);
    void seek2(int seconds);
    void videoAvailable(bool available);

private:
     QMediaPlayer *player;
     QMediaPlayer *player2;
     QPushButton *fullBut;
     Video *videoWin;
     QLabel *play1;
     QLabel *play2;
     QMediaPlaylist *playlistik;
     QMediaPlaylist *playlistik2;
     QSlider *slider1;
     QSlider *slider2;
     qint64 duration;
     QLabel *durLab1;
     QLabel *durLab2;

     void updateDuration(qint64 currentDur, int labNum);
};

#endif // PLAYER_H
