#include <QToolButton>
#include <QSlider>
#include <QStyle>
#include <QBoxLayout>
#include <QFileDialog>
#include "controls.h"

Controls::Controls(QWidget *parent) :
    QWidget(parent),
   statePl(QMediaPlayer::StoppedState), volumeIcon(0), playerMute(false)
{
    toBegin = new QToolButton(this);
    toBegin ->setIcon(QIcon(":/images/backward.png"));
    connect(toBegin, SIGNAL(clicked()), this, SLOT(prevNext()));

    toEnd = new QToolButton(this);
    toEnd ->setIcon(QIcon(":/images/forward.png"));
    connect(toEnd, SIGNAL(clicked()), this, SLOT(prevNext()));

    playBut = new QToolButton(this);
    playBut->setIcon(QIcon(":/images/play.png"));
    connect(playBut, SIGNAL(clicked()), this, SLOT(playClicked()));

    volumeIcon = new QToolButton(this);
    volumeIcon ->setIcon(QIcon(":/images/volume.png"));
    connect(volumeIcon, SIGNAL(clicked()), this, SLOT(muteClick()));

    volSlider = new QSlider(Qt::Horizontal, this);
    volSlider -> setRange(0, 100);
    connect(volSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(volumeChange(int)));
    
    playersCount = new QSpinBox(this);
    playersCount->setRange(0, multiplayer->streamCount());
    connect(playersCount, SIGNAL(valueChanged(int)), this, SLOT(streamChange(int)));

    open = new QPushButton(this);
    open ->setIcon(QIcon(":/images/open.png"));
    connect(open, SIGNAL(clicked()), this, SLOT(openFile()));
    play1 = new QLabel(this);
    play1 ->setText("Choose file");

    QBoxLayout *box = new QHBoxLayout;
    box ->setMargin(0);
    box -> addWidget( open );
    box -> addWidget( toBegin );
    box -> addWidget( playBut );
    box -> addWidget( toEnd );
    box -> addWidget( volumeIcon );
    box -> addWidget( volSlider);
    box->addWidget(playersCount);

    QBoxLayout *main = new QVBoxLayout;
    main->addWidget(play1);
    main->addLayout(box);
    setLayout(main);
}

QMediaPlayer::State Controls::state() const
{
    return statePl;
}

int Controls::volume() const
{
    return volSlider ? volSlider->value() : 0;
}

int Controls::streamNumber() const
{
    return playersCount ? playersCount->value() : 0;
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
        emit play(currentStream);
        break;
    case QMediaPlayer::PlayingState:
        emit pause(currentStream);
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

void Controls::streamChange(int stream)
{
   if(playersCount)
       stream = playersCount->value();
   currentStream = stream;
}

void Controls::prevNext()
{
    if(toBegin->isDown())
        emit backward(currentStream);
    else if(toEnd->isDown())
        emit forward(currentStream);
}

void Controls::openFile()
{
    QString uri = QFileDialog::getOpenFileName(this, "Open media", "", "Media files(*)");    
    multiplayer->setMediaURI(currentStream, uri);
    play1->setText(uri);
}

