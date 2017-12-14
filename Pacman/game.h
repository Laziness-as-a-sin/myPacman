#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "pacman.h"

class Game: public QGraphicsView {
public:
    Game(QWidget *parent = 0);

    QGraphicsScene *scene;
    Pacman *pacman;
};

#endif // GAME_H
