#include "player.h"
#include <QtWidgets>
#include <QMediaService>

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Player");
    setGeometry(100, 100, 600, 400);
    videoWin = new Video(this);

    Controls* controls = new Controls(this);
    //controls->setState(player->state());
    //controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());

    fullBut = new QPushButton(this);
    fullBut ->setIcon(QIcon(":/images/full.png"));
    fullBut->setCheckable(true);

    slider1 = new QSlider(Qt::Horizontal, this);
    //slider1->setRange(0, player->duration()/1000);

    durLab1 = new QLabel(this);
    addBut = new QPushButton(this);
    addBut->setText("Add stream");
    delBut = new QPushButton(this);
    delBut->setText("Delete stream");

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1 ->setMargin(0);
    layout1->addWidget(addBut);
    layout1->addWidget(delBut);
    layout1->addWidget(fullBut);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3 ->addWidget(slider1);
    layout3 ->addWidget(durLab1);

    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->addWidget(videoWin, 2);
    mainLay->addLayout(layout3);
    mainLay->addLayout(layout1);
    mainLay->addWidget(controls);
    setLayout(mainLay);

    connect(addBut, SIGNAL(clicked()), this, SLOT(newStream()));
    
    connect(controls, SIGNAL(play(int)), player, SLOT(play(int)));
    connect(controls, SIGNAL(pause(int)), player, SLOT(pause(int)));
    //connect(controls, SIGNAL(volumeChange(int)), players, SLOT(setVolume(int)));
    //connect(players, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
    
    //connect(controls, SIGNAL(backward(int)), this, SLOT(prevClick(int)));
    //connect(controls, SIGNAL(forward(int)), this, SLOT(nextClick(int)));

    //connect(controls, SIGNAL(muteChange(bool)), players, SLOT(setMuted(bool)));
    //connect(players, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

    //connect(players, SIGNAL(durationChanged(qint64)), SLOT(durationChange(qint64)));
    //connect(players, SIGNAL(positionChanged(qint64)), SLOT(positionChange(qint64)));
    //connect(slider1, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    //connect(players, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailable(bool)));
}

void Player::prevClick(int num)
{
    //int i = num-1;
    //players[i].setPosition(0);
}

void Player::nextClick(int num)
{
    //int i = num-1;
    //players[i].setPosition(player-> position() + 5000);
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
    //players.setPosition(seconds*1000);
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

void Player::newStream()
{
    player->addStream();
}







