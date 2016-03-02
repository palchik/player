#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlaylist>
#include <QVBoxLayout>
#include "video.h"
#include "controls.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);

signals:
    void screenChanged(bool fullScreen);
private slots:
    void prevClick(int num);
    void nextClick(int num);
    void durationChange(qint64 duration);
    void positionChange(qint64 position);
    void seek(int seconds);
    void newStream();

    void videoAvailable(bool available);

private:
     QPushButton *fullBut;
     Video *videoWin;        
     QSlider *slider1;    
     qint64 duration;
     QLabel *durLab1;
     QPushButton *addBut;
     QPushButton *delBut;
     MultiPlayer *player;

     void updateDuration(qint64 currentDur);
};

#endif // PLAYER_H
