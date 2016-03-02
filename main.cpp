#include "multiplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Multiplayer player;
    player.show();
    return app.exec();
}

