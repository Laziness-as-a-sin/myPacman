#include "game.h"
#include "pacman.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent) {
    //create scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    pacman = new Pacman();
    pacman->setPos(400, 500);
    pacman->setFlag(QGraphicsItem::ItemIsFocusable);
    pacman->setFocus();

    scene->addItem(pacman);
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    show();
}
