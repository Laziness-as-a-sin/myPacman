#include "pacman.h"

PacMan::PacMan(QObject *parent) : QObject(parent), QGraphicsItem()
{
    angle = 0;
    setRotation(angle);
    SpritePos = 0;
    SpriteImage = new QPixmap(":s4");
}

QRectF PacMan::boundingRect() const
{
    return QRectF(-25, -25, 50, 50);
}

void PacMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->setBrush(Qt::yellow);
    //painter->drawEllipse(-10, -10, 20, 20);
    painter->drawPixmap(-10,-10, *SpriteImage, SpritePos, 0, 20,20);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PacMan::NextFrame);
    //timer->start(50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void PacMan::MoveOnTime()
{
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                       << mapToScene(0, 0)
                                                       << mapToScene(-10, 12)
                                                       << mapToScene(10, 12));
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;
        emit signalCheckItem(item);
    }

    SpritePos += 20;
    if (SpritePos >= 80 ) SpritePos = 0;

    setPos(mapToParent(0, Vx));

    if(this->x() - 10 < -260){
        this->setX(250);
    }
    if(this->x() + 10 > 260){
        this->setX(-250);
    }
    if(this->y() - 10 < -260){
        this->setY(250);
    }
    if(this->y() + 10 > 260){
        this->setY(-250);
    }

    if(GetAsyncKeyState(VK_LEFT)){
        angle = 90;
        setRotation(angle);
        Vx = 1;
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        angle = 270;
        setRotation(angle);
        Vx = 1;
    }
    if(GetAsyncKeyState(VK_UP)){
        angle = 180;
        setRotation(angle);
        Vx = 1;
    }
    if(GetAsyncKeyState(VK_DOWN)){
        angle = 0;
        setRotation(angle);
        Vx = 1;
    }
}

void PacMan::PushButton(int agle)
{

}

void PacMan::NextFrame(){
    SpritePos += 20;
    if (SpritePos >= 80 ) SpritePos = 0;
    this->update(-10,-10,20,20);
}

void PacMan::stop()
{
    Vx = 0;
}

void PacMan::go()
{
    Vx = 1;
}
