#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <QMediaPlayer>

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

signals:
  void  play();
  void  pause();
  void  forward();
  void  backward();
  void  volumeChange(int volume);
  void  muteChange(bool muting);

public slots:
  void setState(QMediaPlayer::State state);
  void setVolume(int volume);
  void setMuted(bool muted);

private slots:
  void  playClicked();
  void muteClick();

private:
   QAbstractButton *toBegin;
   QAbstractButton *toEnd;
   QAbstractButton *playBut;
   QAbstractButton *volumeIcon;
   QSlider *volSlider;
   QMediaPlayer::State statePl;
   bool playerMute;
};

#endif // CONTROLS_H
