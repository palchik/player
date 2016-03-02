#include "player.h"
#include "controls.h"
#include <QtWidgets>
#include <QMediaService>
#include <QFileDialog>

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    player = new QMediaPlayer(this);
    videoWin = new Video(this);
    player->setVideoOutput(videoWin);

    playlistik = new QMediaPlaylist();
    player->setPlaylist(playlistik);

    Controls *controls1 = new Controls(this);
    controls1->setState(player->state());
    controls1->setVolume(player->volume());
    controls1->setMuted(controls1->isMuted());

    QPushButton *open = new QPushButton(this);
    open ->setIcon(QIcon(":/images/open.png"));

    play1 = new QLabel(this);
    play1 ->setText("Choose file");

    fullBut = new QPushButton(this);
    fullBut ->setIcon(QIcon(":/images/full.png"));
    fullBut->setCheckable(true);

    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setRange(0, player->duration()/1000);

    durLab1 = new QLabel(this);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1 ->setMargin(0);
    layout1 ->addWidget(open);
    layout1 ->addWidget(controls1);
    layout1->addStretch(1);
    layout1->addWidget(fullBut);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3 ->addWidget(slider1);
    layout3 ->addWidget(durLab1);

    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->addWidget(videoWin,2);
    mainLay->addWidget(play1);
    mainLay->addLayout(layout3);
    mainLay->addLayout(layout1);
    setLayout(mainLay);

     connect(open, SIGNAL(clicked()), this, SLOT(openFile()));

     connect(controls1, SIGNAL(play()), player, SLOT(play()));
     connect(controls1, SIGNAL(pause()), player, SLOT(pause()));
     connect(controls1, SIGNAL(volumeChange(int)), player, SLOT(setVolume(int)));
     connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls1, SLOT(setState(QMediaPlayer::State)));

    connect(controls1, SIGNAL(backward()), this, SLOT(prevClick()));
    connect(controls1, SIGNAL(forward()), this, SLOT(nextClick()));

    connect(controls1, SIGNAL(muteChange(bool)), player, SLOT(setMuted(bool)));
    connect(player, SIGNAL(mutedChanged(bool)), controls1, SLOT(setMuted(bool)));

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChange(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChange(qint64)));
    connect(slider1, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailable(bool)));
}

void Player::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open media", "", "Media files(*)");
    playlistik->clear();
    playlistik->addMedia(QUrl::fromLocalFile(filename));
    play1->setText(filename);   
}

void Player::prevClick()
{
    player->setPosition(0);

}
void Player::nextClick()
{
    player->setPosition(player-> position() + 5000);
}

void Player::durationChange(qint64 duration)
{
    this->duration = duration/1000;
    slider1->setMaximum(duration/1000);
}

void Player::positionChange(qint64 position)
{
    if(!slider1->isSliderDown()){
        slider1->setValue(position/1000);
    }
    updateDuration(position/1000);
}

void Player::seek(int seconds)
{
    player->setPosition(seconds*1000);
}

void Player::updateDuration(qint64 currentDur)
{
    QString str;
    if(currentDur || duration) {
        QTime currentTime((currentDur/3600)%60, (currentDur/60)%60, currentDur%60, (currentDur*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if(duration >= 3600)
            format = "hh:mm:ss";
        str = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    durLab1->setText(str);
}
void Player::videoAvailable(bool available)
{
    if(!available) {
        disconnect(fullBut, SIGNAL(clicked(bool)), videoWin, SLOT(setFullScreen(bool)));
        disconnect(videoWin, SIGNAL(screenChanged(bool)), fullBut, SLOT(setChecked(bool)));
        videoWin->setFullScreen(false);
    } else {

        connect(fullBut, SIGNAL(clicked(bool)), videoWin, SLOT(setFullScreen(bool)));
        connect(videoWin, SIGNAL(screenChanged(bool)), fullBut, SLOT(setChecked(bool)));
        if (fullBut->isChecked())
            videoWin->setFullScreen(true);
    }
}






