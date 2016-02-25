#ifndef AUDIPPLAYER_H
#define AUDIPPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMediaPlaylist>

class AudipPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit AudipPlayer(QWidget *parent = 0);

signals:

private slots:
    void openFile2();
    void prevClick2();
    void nextClick2();
    void durationChange2(qint64 duration);
    void positionChange2(qint64 position);
    void seek2(int seconds);

private:
    QMediaPlayer *player2;
    QLabel *play2;
    QMediaPlaylist *playlistik2;
    QSlider *slider2;
    QLabel *durLab2;
    qint64 duration;
    void updateDuration(qint64 currentDur);

};

#endif // AUDIPPLAYER_H
