#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

class Ghost : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Ghost(QObject *parent = 0);
    void mapInit(bool map[24][24]);
    int counter = 0, Vx, Vy;
    bool KeyA = 1, stop;
    int paths[24][24];
    bool bmap[24][24];
signals:

public slots:
    void MoveOnTime();

private slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int mx, my;
    QTimer *timer;
    bool turnUP, turnDOWN, turnLEFT, turnRIGHT;
};

#endif // GHOST_H
