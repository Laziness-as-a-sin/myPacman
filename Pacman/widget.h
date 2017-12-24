#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QPainter>

#include <pacman.h>
#include <wallblock.h>
#include <ghost.h>
#include <piece.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QList<QGraphicsItem *> wallblocks;
    QList<Ghost *> ghosts;
    QList<QGraphicsItem *> pieces;
    QPixmap d;
    QGraphicsItem *dl;

    QGraphicsScene *scene;
    Ghost *ghost;
    PacMan *pacman;    
    QTimer *timer;
    double countscope = 0, countdeath = 0;
    bool die = 0;

    void incrementScore();
    void death();
    void restart();
    void keyPressEvent(QKeyEvent *);

private slots:
     void stop(QGraphicsItem * item);
     void revive();
};

#endif // WIDGET_H
