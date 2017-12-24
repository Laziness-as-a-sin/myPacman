#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

class PacMan : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PacMan(QObject *parent = 0);
    void stop();
    void go();
    void die();
    bool KeyA = 1, pacd = 0;

signals:
    void signalCheckItem(QGraphicsItem *item);

public slots:
    void MoveOnTime();

private slots:
    void NextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int Vx, Vy, angle, SpritePos;
    QPixmap *SpriteImage, *Pixm;
    QTimer *timer;
};

#endif // PACMAN_H