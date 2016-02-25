#include "mainwin.h"
#include <QtWidgets>

MainWin::MainWin(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Player");
    setGeometry(100, 100, 800, 600);
    audio = new AudipPlayer(this);
    audio2 = new AudipPlayer(this);
    video = new Player(this);

    QVBoxLayout *winLay = new QVBoxLayout;
    winLay->addWidget(video);
    winLay->addWidget(audio);
    winLay->addWidget(audio2);
    setLayout(winLay);
}
