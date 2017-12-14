#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "gameobject.h"
#include <QObject>

class Pacman: public GameObject, public QGraphicsPixmapItem, public QObject {
    Q_OBJECT
    int state;
public:
    Pacman(QGraphicsItem *parent = 0);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void move();
};

#endif // PACMAN_H
