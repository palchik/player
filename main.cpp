#include "mainwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWin player;
    player.show();
    return app.exec();
}

