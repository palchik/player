#include "controls.h"
#include <QToolButton>
#include <QSlider>
#include <QStyle>
#include <QHBoxLayout>

Controls::Controls(QWidget *parent) :
    QWidget(parent),
   statePl(QMediaPlayer::StoppedState), volumeIcon(0), playerMute(false)
{
    toBegin = new QToolButton(this);
    toBegin ->setIcon(QIcon(":/images/backward.png"));
    connect(toBegin, SIGNAL(clicked()), this, SIGNAL(backward()));

    toEnd = new QToolButton(this);
    toEnd ->setIcon(QIcon(":/images/forward.png"));
    connect(toEnd, SIGNAL(clicked()), this, SIGNAL(forward()));

    playBut = new QToolButton(this);
    playBut->setIcon(QIcon(":/images/play.png"));
    connect(playBut, SIGNAL(clicked()), this, SLOT(playClicked()));

    volumeIcon = new QToolButton(this);
    volumeIcon ->setIcon(QIcon(":/images/volume.png"));

    connect(volumeIcon, SIGNAL(clicked()), this, SLOT(muteClick()));

    volSlider = new QSlider(Qt::Horizontal, this);
    volSlider -> setRange(0, 100);
    connect(volSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(volumeChange(int)));

    QHBoxLayout *box = new QHBoxLayout;
    box ->setMargin(0);
    box -> addWidget( toBegin );
    box -> addWidget( playBut );
    box -> addWidget( toEnd );
    box -> addWidget( volumeIcon );
    box -> addWidget( volSlider);
    setLayout(box);
}

QMediaPlayer::State Controls::state() const
{
    return statePl;
}

int Controls::volume() const
{
    return volSlider ? volSlider->value() : 0;
}

void Controls::setState(QMediaPlayer::State state)
{
    if(state != statePl) {
        statePl = state;

    switch (state) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        playBut->setIcon(QIcon(":/images/play.png"));
        break;
    case QMediaPlayer::PlayingState:
        playBut->setIcon(QIcon(":/images/pause.png"));
        break;
    }
  }
}

void Controls::playClicked()
{
    switch (statePl) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }

}

void Controls::setVolume(int volume)
{
    if(volSlider)
        volSlider->setValue(volume);
}

bool Controls::isMuted() const
{
    return playerMute;
}

void Controls::setMuted(bool muted)
{
    if(muted != playerMute){
        playerMute = muted;

        if(muted){
            volumeIcon->setIcon(QIcon(":/images/no.png"));
        } else {
            volumeIcon->setIcon(QIcon(":/images/volume.png"));
        }
    }
}

void Controls::muteClick()
{
    emit muteChange(!playerMute);
}
