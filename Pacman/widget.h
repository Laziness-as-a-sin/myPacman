#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>

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
    QList<QGraphicsItem *> wallblocks;
    QList<QGraphicsItem *> ghosts;
    QList<QGraphicsItem *> pieces;
    Ui::Widget *ui;
    QGraphicsScene *scene;
    //Ghost *ghost;
    PacMan *pacman;
    //WallBlock *wallblock;    
    QTimer *timer;
    double countscope = 0;
    double countdeath = 0;

private slots:
     void stop(QGraphicsItem * item);
};

#endif // WIDGET_H
