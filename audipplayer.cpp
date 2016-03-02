#include "audipplayer.h"
#include "controls.h"
#include <QtWidgets>
#include <QMediaService>
#include <QFileDialog>

AudipPlayer::AudipPlayer(QWidget *parent) :
    QWidget(parent)
{
    player2 = new QMediaPlayer(this);
    playlistik2 = new QMediaPlaylist();
    player2->setPlaylist(playlistik2);

    Controls *controls2 = new Controls(this);
    controls2->setState(player2->state());
    controls2->setVolume(player2->volume());
    controls2->setMuted(controls2->isMuted());

    QPushButton *open2 = new QPushButton(this);
    open2 ->setIcon(QIcon(":/images/open2.png"));

    play2 = new QLabel(this);
    play2 ->setText("Choose file");

    slider2 = new QSlider(Qt::Horizontal, this);
    slider2->setRange(0, player2->duration()/1000);
    durLab2 = new QLabel(this);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2 ->setMargin(0);
    layout2 ->addWidget(open2);
    layout2->addWidget(controls2);
    layout2->addStretch(1);

    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4 ->addWidget(slider2);
    layout4 ->addWidget(durLab2);

    QVBoxLayout *mainLay = new QVBoxLayout;
    mainLay->addWidget(play2);
    mainLay->addLayout(layout4);
    mainLay->addLayout(layout2);
    setLayout(mainLay);

    connect(open2, SIGNAL(clicked()), this, SLOT(openFile2()));
    connect(controls2, SIGNAL(play()), player2, SLOT(play()));
    connect(controls2, SIGNAL(pause()), player2, SLOT(pause()));
    connect(controls2, SIGNAL(volumeChange(int)), player2, SLOT(setVolume(int)));
    connect(player2, SIGNAL(stateChanged(QMediaPlayer::State)), controls2, SLOT(setState(QMediaPlayer::State)));

    connect(controls2, SIGNAL(backward()), this, SLOT(prevClick2()));
    connect(controls2, SIGNAL(forward()), this, SLOT(nextClick2()));

    connect(controls2, SIGNAL(muteChange(bool)), player2, SLOT(setMuted(bool)));
    connect(player2, SIGNAL(mutedChanged(bool)), controls2, SLOT(setMuted(bool)));

    connect(player2, SIGNAL(durationChanged(qint64)), SLOT(durationChange2(qint64)));
    connect(player2, SIGNAL(positionChanged(qint64)), SLOT(positionChange2(qint64)));
    connect(slider2, SIGNAL(sliderMoved(int)), this, SLOT(seek2(int)));
}

void AudipPlayer::openFile2()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open media", "", "Media files(*)");
    playlistik2->clear();
    playlistik2->addMedia(QUrl::fromLocalFile(filename));
    play2->setText(filename);
}

void AudipPlayer::prevClick2()
{
    player2->setPosition(0);

}

void AudipPlayer::nextClick2()
{
    player2->setPosition(player2-> position() + 5000);
}

void AudipPlayer::durationChange2(qint64 duration)
{
    this->duration = duration/1000;
    slider2->setMaximum(duration/1000);
}

void AudipPlayer::positionChange2(qint64 position)
{
    if(!slider2->isSliderDown()){
        slider2->setValue(position/1000);
    }
    updateDuration(position/1000);
}

void AudipPlayer::seek2(int seconds)
{
    player2->setPosition(seconds*1000);
}

void AudipPlayer::updateDuration(qint64 currentDur)
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
    durLab2->setText(str);
}
