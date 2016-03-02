#include "multiplayer.h"

Multiplayer::Multiplayer(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Player");
    setGeometry(100, 100, 600, 400);
    addBut = new QPushButton(this);
    addBut->setText("Add stream");
    player = new Player(this);

    lay = new QVBoxLayout;
    lay->addWidget(addBut);
    QHBoxLayout *main = new QHBoxLayout;
    main->addWidget(player);
    main->addLayout(lay);
    setLayout(main);

    connect(addBut, SIGNAL(clicked()), this, SLOT(addNewStream()));
}
int Multiplayer::addStream()
{
   AudipPlayer *tmpplayer = new AudipPlayer(this);
   players.append(tmpplayer);
   int pos = players.size();
    int i = pos+1;
    if(players.size()>0){
        for(int j=0; j<=players.size(); j++){

            lay->addWidget(tmpplayer);
        }
    }
    qDebug() << "Number of streams: " << i;
    return i;
}

void Multiplayer::addNewStream()
{
    addStream();
}


