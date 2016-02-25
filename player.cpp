#include "player.h"
#include "controls.h"
#include <QtWidgets>
#include <QMediaService>
#include <QFileDialog>

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Player");
    setGeometry(100, 100, 600, 400);
    player = new QMediaPlayer(this);
    player2 = new QMediaPlayer(this);
    videoWin = new Video(this);
    player->setVideoOutput(videoWin);

    playlistik = new QMediaPlaylist();
    player->setPlaylist(playlistik);
    playlistik2 = new QMediaPlaylist();
    player2->setPlaylist(playlistik2);

    Controls *controls1 = new Controls(this);
    controls1->setState(player->state());
    controls1->setVolume(player->volume());
    controls1->setMuted(controls1->isMuted());

    Controls *controls2 = new Controls(this);
    controls2->setState(player2->state());
    controls2->setVolume(player2->volume());
    controls2->setMuted(controls2->isMuted());

    QPushButton *open = new QPushButton(this);
    open ->setIcon(QIcon(":/images/open.png"));

    QPushButton *open2 = new QPushButton(this);
    open2 ->setIcon(QIcon(":/images/open2.png"));

    play1 = new QLabel(this);
    play1 ->setText("Choose file");
    play2 = new QLabel(this);
    play2 ->setText("Choose file");

    fullBut = new QPushButton(this);
    fullBut ->setIcon(QIcon(":/images/full.png"));
    fullBut->setCheckable(true);

    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setRange(0, player->duration()/1000);
    slider2 = new QSlider(Qt::Horizontal, this);
    slider2->setRange(0, player2->duration()/1000);

    durLab1 = new QLabel(this);
    durLab2 = new QLabel(this);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1 ->setMargin(0);
    layout1 ->addWidget(open);
    layout1 ->addWidget(controls1);
    layout1->addStretch(1);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2 ->setMargin(0);
    layout2 ->addWidget(open2);
    layout2->addWidget(controls2);
    layout2->addStretch(1);
    layout2->addWidget(fullBut);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3 ->addWidget(slider1);
    layout3 ->addWidget(durLab1);

    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4 ->addWidget(slider2);
    layout4 ->addWidget(durLab2);

    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->addWidget(videoWin, 2);
    mainLay->addWidget(play1);
    mainLay->addLayout(layout3);
    mainLay->addLayout(layout1);
    mainLay->addWidget(play2);
    mainLay->addLayout(layout4);
    mainLay->addLayout(layout2);
    setLayout(mainLay);

     connect(open, SIGNAL(clicked()), this, SLOT(openFile()));
     connect(open2, SIGNAL(clicked()), this, SLOT(openFile2()));

     connect(controls2, SIGNAL(play()), player2, SLOT(play()));
     connect(controls2, SIGNAL(pause()), player2, SLOT(pause()));
     connect(controls2, SIGNAL(volumeChange(int)), player2, SLOT(setVolume(int)));
     connect(player2, SIGNAL(stateChanged(QMediaPlayer::State)), controls2, SLOT(setState(QMediaPlayer::State)));

     connect(controls1, SIGNAL(play()), player, SLOT(play()));
     connect(controls1, SIGNAL(pause()), player, SLOT(pause()));
     connect(controls1, SIGNAL(volumeChange(int)), player, SLOT(setVolume(int)));
     connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), controls1, SLOT(setState(QMediaPlayer::State)));

    connect(controls1, SIGNAL(play()), player2, SLOT(pause()));
    connect(controls2, SIGNAL(play()), player, SLOT(pause()));

    connect(controls1, SIGNAL(backward()), this, SLOT(prevClick()));
    connect(controls1, SIGNAL(forward()), this, SLOT(nextClick()));

    connect(controls2, SIGNAL(backward()), this, SLOT(prevClick2()));
    connect(controls2, SIGNAL(forward()), this, SLOT(nextClick2()));

    connect(controls1, SIGNAL(muteChange(bool)), player, SLOT(setMuted(bool)));
    connect(player, SIGNAL(mutedChanged(bool)), controls1, SLOT(setMuted(bool)));

    connect(controls2, SIGNAL(muteChange(bool)), player2, SLOT(setMuted(bool)));
    connect(player2, SIGNAL(mutedChanged(bool)), controls2, SLOT(setMuted(bool)));

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChange(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChange(qint64)));
    connect(slider1, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    connect(player2, SIGNAL(durationChanged(qint64)), SLOT(durationChange2(qint64)));
    connect(player2, SIGNAL(positionChanged(qint64)), SLOT(positionChange2(qint64)));
    connect(slider2, SIGNAL(sliderMoved(int)), this, SLOT(seek2(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailable(bool)));
}

void Player::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open media", "", "Media files(*)");
    playlistik->clear();
    playlistik->addMedia(QUrl::fromLocalFile(filename));
    play1->setText(filename);   
}

void Player::openFile2()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open media", "", "Media files(*)");
    playlistik2->clear();
    playlistik2->addMedia(QUrl::fromLocalFile(filename));
    play2->setText(filename);   
}

void Player::prevClick()
{
    player->setPosition(0);

}
void Player::nextClick()
{
    player->setPosition(player-> position() + 5000);
}

void Player::prevClick2()
{
    player2->setPosition(0);

}
void Player::nextClick2()
{
    player2->setPosition(player-> position() + 5000);
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
    updateDuration(position/1000, 1);
}

void Player::seek(int seconds)
{
    player->setPosition(seconds*1000);
}

void Player::durationChange2(qint64 duration)
{
    this->duration = duration/1000;
    slider2->setMaximum(duration/1000);
}

void Player::positionChange2(qint64 position)
{
    if(!slider2->isSliderDown()){
        slider2->setValue(position/1000);
    }
    updateDuration(position/1000, 2);
}

void Player::seek2(int seconds)
{
    player2->setPosition(seconds*1000);
}

void Player::updateDuration(qint64 currentDur, int labNum)
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
    if (labNum == 1)
    durLab1->setText(str);
    else if (labNum == 2)
    durLab2->setText(str);
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






