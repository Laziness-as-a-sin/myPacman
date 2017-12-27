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
    QFile file(":lvl1");
    QByteArray block;
    if(!file.open(QIODevice::ReadOnly))
    {qDebug() <<  "Cannot open a file";}else{
       block = file.readAll();

        int x = -240,y = -240;
       // for(int p = 0; p < 30; p++){
       for(int i = 0; i < 650; i++){
       if (block[i] == '+'){

           WallBlock *wallblock = new WallBlock();
           scene->addItem(wallblock);
           wallblock->setPos(x, y);
           wallblocks.append(wallblock);
           x += 20;
       }else if(block[i] == '-') {
           Piece *piece = new Piece();
           scene->addItem(piece);
           piece->setPos(x, y);
           pieces.append(piece);
           x += 20;
       }else if(block[i] == '.'){
           x += 20;
       }else if(block[i] == '*'){
           x = -240;
           y += 20;
        }

}
    }
    /*for(int i = -250; i < 13; i++)//стеночки
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
    for(int i = -250; i < 13; i++)//стеночки
    {
        WallBlock *wallblock = new WallBlock();
        scene->addItem(wallblock);
        wallblock->setPos(i*20, -240);
        wallblocks.append(wallblock);
    }
    for(int i = -250; i < 13; i++)//стеночки
    {
        WallBlock *wallblock = new WallBlock();
        scene->addItem(wallblock);
        wallblock->setPos(-40, i*20);
        wallblocks.append(wallblock);
    }*/
    /*for(int i = -250; i < 13; i++)//куски
    {
        Piece *piece = new Piece();
        scene->addItem(piece);
        piece->setPos(0, i*20);
        pieces.append(piece);
    }*/


    ghost = new Ghost();
    scene->addItem(ghost);
    ghost->setPos(0, 60);
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
    pacman->stop();
    pacman->setPos(0, 0);
    foreach (QGraphicsItem *ghost, ghosts)
    {
        ghost->setPos(0, 60);
       // ghost->Vy = 0;
    }
    int curLifes = (ui->lifesLabel->text().split(" ")[1].toInt() - 1);
    ui->lifesLabel->setText("LIFES: " + QString::number(curLifes));


    if(curLifes == 0){
        ui->infoLabel->setText("Restarting...");
        Sleep(1000);
        ui->infoLabel->setText("");
        restart();
    }
    scene->update();
#ifdef Q_OS_WIN
    Sleep(1000);
#endif

}

void Widget::restart() {
    pacman->setPos(0, 0);

    foreach(QGraphicsItem *ghost, ghosts) {
        scene->removeItem(ghost);
        ghosts.removeOne(ghost);
        delete ghost;
    }

    foreach(QGraphicsItem *piece, pieces) {
        scene->removeItem(piece);
        pieces.removeOne(piece);
        delete piece;
    }
    for(int i = -250; i < 13; i++) {
        Piece *piece = new Piece();
        scene->addItem(piece);
        piece->setPos(0, i*20);
        pieces.append(piece);
    }

    ghost = new Ghost();
    scene->addItem(ghost);
    ghost->setPos(0, 60);
    ghosts.append(ghost);

    ui->scoreLabel->setText("SCORE: 0");
    ui->lifesLabel->setText("LIFES: 3");
}

void Widget::revive() {
    pacman->go();
    //ghost->Vy = 1;
}
