#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QWidget>
#include <QBoxLayout>
#include "player.h"
#include "audipplayer.h"

class Multiplayer : public QWidget
{
    Q_OBJECT
public:
    explicit Multiplayer(QWidget *parent = 0);
     int addStream();

signals:

public slots:
     void addNewStream();

private:
     Player *player;
     QPushButton *addBut;
     QBoxLayout *lay;
     QVector<AudipPlayer *> players;
};

#endif // MULTIPLAYER_H
