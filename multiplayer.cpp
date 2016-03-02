#include "multiplayer.h"
#include "controls.h"
#include <QDebug>

MultiPlayer::MultiPlayer(QObject *parent) :
    QObject(parent)
{
}

//Добавить поток (возвращаем номер добавленного потока)
int MultiPlayer::addStream()
{
    QMediaPlayer* tmpplayer = new QMediaPlayer(this);
    QMediaPlaylist* tmpplaylist = new QMediaPlaylist(this);
    tmpplayer->setPlaylist(tmpplaylist);
    int pos = players.size();
    players.append(tmpplayer);
    playlists.append(tmpplaylist);
    int i = pos+1;
    qDebug() << "Number of streams: " << i;
    return i;
}

//Удалить поток (если был) вернуть true в случае успеха
bool MultiPlayer::delStream(int number)
{
    int pos = players.size() + 1;
    if(pos <= number){
    players.remove(number);
    return true;
    }
}

//Управление потоками
void MultiPlayer::pause(int number){
    int i = number -1;
    players[i]->pause();
}

void MultiPlayer::play(int number){
    int i = number -1;
    players[i]->play();
}

//
/*bool MultiPlayer::attachVideoWidget(int number, Video &widget){
    int i = number -1;
    players[i].setVideoOutput(widget);
    return true;
}

bool MultiPlayer::detachVideoWidget(int number){
    int i = number -1;
    players[i].setVideoOutput();
    return true;
}*/

//
bool MultiPlayer::setVolume(int number, int volume)
{
  int i = number -1;
  players[i]->setVolume(volume);
  return true;
}

//
int MultiPlayer::streamCount()
{
    int streams = players.size();
    return streams +1;
}

//Открыть файл/URL для потока
bool MultiPlayer::setMediaURI(int number, QString uri)
{
    playlists[number]->clear();
    playlists[number]->addMedia(QUrl::fromLocalFile(uri));
    return true;
}
