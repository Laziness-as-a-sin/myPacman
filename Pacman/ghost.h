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
    void stop();
    void go();
    void mapInit(bool map[24][24]);
    int counter = 0, Vx, Vy;
    bool KeyA = 1;
    int paths[24][24];
    bool bmap[24][24];
signals:
    //void signalCheckItem(QGraphicsItem *item);

public slots:
    //void PushButton(int);
    void MoveOnTime();

private slots:
    //void NextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int mx, my;
    //QPixmap *SpriteImage;
    QTimer *timer;
    bool turnUP, turnDOWN, turnLEFT, turnRIGHT;
};

#endif // GHOST_H
