#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "multiplayer.h"

class QAbstractButton;
class QSlider;

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QWidget *parent = 0);
    QMediaPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
    int streamNumber() const;
    int currentStream;

signals:
  void  play(int number);
  void  pause(int number);
  void  forward(int number);
  void  backward(int number);
  void  volumeChange(int volume);
  void  muteChange(bool muting);
  void newStr(int number);

public slots:
  void setState(QMediaPlayer::State state);
  void setVolume(int volume);
  void setMuted(bool muted);
  void streamChange(int stream);

private slots:
  void  playClicked();
  void  prevNext();
  void muteClick();
   void openFile();

private:
   QAbstractButton *toBegin;
   QAbstractButton *toEnd;
   QAbstractButton *playBut;
   QAbstractButton *volumeIcon;
   QAbstractButton *open;
   QSlider *volSlider;
   QMediaPlayer::State statePl;
   bool playerMute;
   QSpinBox *playersCount;   
   QLabel *play1;
   MultiPlayer *multiplayer;
};

#endif // CONTROLS_H
