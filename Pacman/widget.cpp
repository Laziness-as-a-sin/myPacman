#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,600);
    this->setFixedSize(600,600);
    this->setStyleSheet("background-color: black");

    scene = new QGraphicsScene();
    pacman = new PacMan();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->graphicsView->setStyleSheet("QGraphicsView{border-style:none;}");

    ui->lifesLabel->setReadOnly(true);
    ui->scoreLabel->setReadOnly(true);
    ui->infoLabel->setReadOnly(true);

    ui->lifesLabel->setStyleSheet("color: yellow; border-style:none");
    ui->scoreLabel->setStyleSheet("color: yellow; border-style: none");
    ui->infoLabel->setStyleSheet("color: yellow; border-style: none");

    ui->lifesLabel->setText("LIFES: 3");
    ui->scoreLabel->setText("SCORE: 0");

    scene->setSceneRect(-250,-250,500,500);

    //scene->addLine(-250,0,250,0,QPen(Qt::black));
    //scene->addLine(0,-250,0,250,QPen(Qt::black));

    //scene->addLine(-250,-250, 250,-250, QPen(Qt::black));
    //scene->addLine(-250, 250, 250, 250, QPen(Qt::black));
    //scene->addLine(-250,-250,-250, 250, QPen(Qt::black));
    //scene->addLine( 250,-250, 250, 250, QPen(Qt::black));

    scene->addItem(pacman);
    pacman->setPos(0, 0);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, pacman, &PacMan::MoveOnTime);
    //connect(timer, &QTimer::timeout, ghost, &Ghost::MoveOnTime);
    timer->start(1000 / 200);

    connect(pacman, &PacMan::signalCheckItem, this, &Widget::stop);

    for(int i = -250; i < 13; i++)//стеночки
    {
        WallBlock *wallblock = new WallBlock();
        scene->addItem(wallblock);
        wallblock->setPos(-40, i*20);
        wallblocks.append(wallblock);        
    }
    for(int i = -250; i < 13; i++)
    {
        WallBlock *wallblock = new WallBlock();
        scene->addItem(wallblock);
        wallblock->setPos(40, i*20);
        wallblocks.append(wallblock);
    }
    for(int i = -250; i < 13; i++)//куски
    {
        Piece *piece = new Piece();
        scene->addItem(piece);
        piece->setPos(0, i*20);
        pieces.append(piece);
    }

    ghost = new Ghost();
    scene->addItem(ghost);
    pacman->setPos(0, 60);
    ghosts.append(ghost);

}

void Widget::stop(QGraphicsItem *item)//взаимодействие, надо переименовать
{
    foreach (QGraphicsItem *wallblock, wallblocks)
        if(wallblock == item)
        {
            pacman->stop();
        }
    foreach (QGraphicsItem *ghost, ghosts)
        if(ghost == item)
            {
            //needs some work
                death();
            }
    foreach (QGraphicsItem *piece, pieces)
        if(piece == item){
            scene->removeItem(piece);
            pieces.removeOne(item);
            delete piece;
            incrementScore();
        }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::incrementScore() {
    ui->scoreLabel->setText("SCORE: " + QString::number(ui->scoreLabel->text().split(" ")[1].toInt() + 10));
}

void Widget::death() {
    int curLifes = (ui->lifesLabel->text().split(" ")[1].toInt() - 1);
    ui->lifesLabel->setText("LIFES: " + QString::number(curLifes));

    delete ghost;
    pacman->die();
    delete pacman;


    //ИЗБАВИТЬСЯ ОТ SLEEP(!!!)
    for(int i = 5; i > 0; i--) {
        ui->infoLabel->setText("Respawn in " + QString::number(i) + "!");
    #ifdef Q_OS_WIN
        Sleep(1000);
    #endif
    }

    ui->infoLabel->setText("");

    pacman = new PacMan();
    pacman->setPos(0, 0);
    scene->addItem(pacman);
    connect(timer, &QTimer::timeout, pacman, &PacMan::MoveOnTime);
    timer->start(1000 / 200);
    connect(pacman, &PacMan::signalCheckItem, this, &Widget::stop);

    ghost = new Ghost();
    scene->addItem(ghost);
    pacman->setPos(0, 60);
    ghosts.append(ghost);
}
