#include "ghost.h"
#include <QDebug>

Ghost::Ghost(QObject *parent) : QObject(parent), QGraphicsItem()
{
    setRotation(0);
    Vx = 0, Vy = 0;

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ghost::MoveOnTime);
    timer->start(1000/200);

    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            paths[i][j] = 0;
        }
    }
}

QRectF Ghost::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    counter++;
    if(counter > 16)counter = 0;
    //painter->setBrush(Qt::green);
    //painter->drawEllipse(-10, -10, 20, 20);
    painter->setBrush(Qt::green);
    painter->setPen(Qt::green);
    painter->drawEllipse(-10, -10, 20, 10); //верх
    painter->drawRect(-10, -5, 20, 10); //туловище

    painter->drawEllipse(-10, 5, 3, 3);
    painter->drawEllipse(7, 5, 3, 3);

    if(counter > 8)
    painter->drawEllipse(-3, 5, 6, 3);
    else
    {
    painter->drawEllipse(-5, 5, 3, 3);
    painter->drawEllipse(1, 5, 3, 3);
    }

    painter->setBrush(Qt::white); //белки глаз
    painter->drawEllipse(-8, -5, 7, 8);
    painter->drawEllipse(2, -5, 7, 8);

    painter->setBrush(Qt::black); //зрачки
    painter->setPen(Qt::black);
    if(Vy == 1){ //взгляд вниз
    painter->drawEllipse(-6, -2, 3, 3);
    painter->drawEllipse(4, -2, 3, 3);
    }
    if(Vy == -1){ //взгляд вверх
    painter->drawEllipse(-6, -5, 3, 3);
    painter->drawEllipse(4, -5, 3, 3);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ghost::MoveOnTime()
{
    turnRIGHT = 0;
    turnLEFT = 0;
    turnDOWN = 0;
    turnUP = 0;

    if(KeyA){
        if(GetAsyncKeyState(VK_LEFT))go();
        if(GetAsyncKeyState(VK_RIGHT))go();
        if(GetAsyncKeyState(VK_UP))go();
        if(GetAsyncKeyState(VK_DOWN))go();
    }


    qDebug() << my;
    qDebug() << mx;

    if((int)this->y() % 20 == 0 && (int)this->x() % 20 == 0){
        mx = (int)this->x() / 20;
        if(mx <= 0)
            mx = 12-abs(mx);
        else
            mx += 12;

        my = (int)this->y() / 20;
        if(my <= 0)
            my = 12-abs(my);
        else
            my += 12;

        qDebug() << my;
        qDebug() << mx;
        if(bmap[my][mx+1])turnRIGHT = 1;
        if(bmap[my][mx-1])turnLEFT = 1;
        if(bmap[my+1][mx])turnDOWN = 1;
        if(bmap[my-1][mx])turnUP = 1;

        int super_random = qrand() % ((4 + 1) - 1) + 1;
        while(1){
            if(super_random == 1 && turnRIGHT && Vx != -1){Vx = 1; Vy = 0; break;}
            if(super_random == 2 && turnLEFT && Vx != 1){Vx = -1; Vy = 0; break;}
            if(super_random == 3 && turnDOWN && Vy != -1){Vx = 0; Vy = 1; break;}
            if(super_random == 3 && turnUP && Vy != 1){Vx = 0; Vy = -1; break;}
            if(!turnUP && !turnDOWN && !turnLEFT){Vx = 1; Vy = 0; break;}
            if(!turnUP && !turnDOWN && !turnRIGHT){Vx = -1; Vy = 0; break;}
            if(!turnUP && !turnRIGHT && !turnLEFT){Vx = 0; Vy = 1; break;}
            if(!turnRIGHT && !turnDOWN && !turnLEFT){Vx = 0; Vy = -1; break;}
            super_random = qrand() % ((4 + 1) - 1) + 1;
        }

    }


    setPos(mapToParent(Vx, Vy));
    if(this->x() - 10 < -260){
        this->setX(250);
    }
    if(this->x() + 10 > 260){
        this->setX(-250);
    }

}

void Ghost::stop()
{
    Vx = 0;
}

void Ghost::go()
{

}

void Ghost::mapInit(bool map[24][24]) {
    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            bmap[i][j] = map[i][j];
            //сверху
            if(i > 0 && map[i - 1][j]) {
                paths[i][j]++;
            }
            //снизу
            if(i < 23 && map[i + 1][j]) {
                paths[i][j]++;
            }
            //слева
            if(j > 0 && map[i][j - 1]) {
                paths[i][j]++;
            }
            //справа
            if(j < 23 && map[i][j + 1]) {
                paths[i][j]++;
            }
        }
    }

    /*for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            output << paths[i][j] << " ";
        }
        output << "\n";
    }*/

}
