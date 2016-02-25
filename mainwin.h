#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include "audipplayer.h"
#include "player.h"

class MainWin : public QWidget
{
    Q_OBJECT
public:
    explicit MainWin(QWidget *parent = 0);

signals:

public slots:

private:
    AudipPlayer *audio;
    AudipPlayer *audio2;
    Player *video;

};

#endif // MAINWIN_H
