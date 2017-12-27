#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QKeyEvent>

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
    QList<Ghost *> ghosts;
    Ghost *ghost;
    QList<QGraphicsItem *> pieces;
    Ui::Widget *ui;
    QGraphicsScene *scene;
    PacMan *pacman;    
    QTimer *timer;
    double countscope = 0;
    double countdeath = 0;
    bool die = 0;
    void incrementScore();
    void death();
    void restart();
    QByteArray block;
    QPixmap d;
    QGraphicsItem *dl;
    void keyPressEvent(QKeyEvent *);

private slots:
     void stop(QGraphicsItem * item);
     void revive();     
};

#endif // WIDGET_H
