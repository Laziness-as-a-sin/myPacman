#include "ghost.h"

Ghost::Ghost(QObject *parent) : QObject(parent), QGraphicsItem()
{
    angle = 0;
    setRotation(angle);
    Vy = 1;
    //SpriteImage = new QPixmap(":s4");
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ghost::MoveOnTime);
    timer->start(1000/200);
}

QRectF Ghost::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-10, -10, 20, 20);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ghost::MoveOnTime()
{
    setPos(mapToParent(0, Vy));
    if(this->y() - 10 < -260){
        this->setY(250);
    }
    if(this->y() + 10 > 260){
        this->setY(-250);
    }
}
