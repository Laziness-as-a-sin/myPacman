#include "pacman.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

Pacman::Pacman(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/pacman_right.png"));

    state = 3;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(250);
}

void Pacman::move() {
    if(state == 1) {
        setPixmap(QPixmap(":/images/pacman_up.png"));
        if(y() - 16 > 0) {
            setPos(x(), y() - 16);
        }
    }
    else if(state == 2) {
        setPixmap(QPixmap(":/images/pacman_down.png"));
        if(y() - 16 < 600) {
            setPos(x(), y() + 16);
        }
    }
    else if(state == 3) {
        setPixmap(QPixmap(":/images/pacman_left.png"));
        if(x() - 16 > 0) {
            setPos(x() - 16, y());
        }
    }
    else if(state == 4) {
        setPixmap(QPixmap(":/images/pacman_right.png"));
        if(x() + 16 < 800) {
            setPos(x() + 16, y());
        }
    }
}

void Pacman::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Up) {
        state = 1;
    }
    else if(event->key() == Qt::Key_Down) {
        state = 2;
    }
    else if(event->key() == Qt::Key_Left) {
        state = 3;
    }
    else if(event->key() == Qt::Key_Right) {
        state = 4;
    }
}
