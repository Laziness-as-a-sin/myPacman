#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "gameobject.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QRectF>

class Obstacle: public GameObject
{
public:
    QRectF *obstacle;
    Obstacle();
};

#endif // OBSTACLE_H
