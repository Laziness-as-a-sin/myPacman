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

    d = QPixmap(":Die");
    dl = scene->addPixmap(d);
    scene->removeItem(dl);
    w = QPixmap(":Win");
    wl = scene->addPixmap(w);
    scene->removeItem(wl);


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
    ui->scorewin->setStyleSheet("QLabel{background-color: rgba(0, 0, 0, 0);}");
    ui->scorewin->setAlignment(Qt::AlignCenter);

    ui->lifesLabel->setText("LIFES: 3");
    ui->scoreLabel->setText("SCORE: 0");

    scene->setSceneRect(-250,-250,500,500);

    scene->addItem(pacman);
    pacman->setPos(0, 0);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, pacman, &PacMan::MoveOnTime);
    connect(timer, &QTimer::timeout, this, &Widget::timeplus);
    timer->start(1000 / 200);


    connect(pacman, &PacMan::signalCheckItem, this, &Widget::stop);
    QFile lvl1(":lvl1"), lvl2(":lvl2"), lvl3(":lvl3");

    if(!lvl1.open(QIODevice::ReadOnly))
    {qDebug() <<  "Cannot open a file";}else{
       block1 = lvl1.readAll();
    }
    if(!lvl2.open(QIODevice::ReadOnly))
    {qDebug() <<  "Cannot open a file";}else{
       block2 = lvl2.readAll();
    }

    nextlevel(1);
}

void Widget::timeplus(){
    finaltime++;
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
                death();
            }
    foreach (QGraphicsItem *piece, pieces)
        if(piece == item){
            scene->removeItem(piece);
            pieces.removeOne(item);
            delete piece;
            incrementScore();
            if(pieces.isEmpty()) {
                winscene();
            }
        }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::incrementScore() {
    score += 10;
    ui->scoreLabel->setText("SCORE: " + QString::number(score));
    if(score == 1910){
        level++;
        nextlevel(level);
    }

}

void Widget::death() {
    int curLifes = (ui->lifesLabel->text().split(" ")[1].toInt() - 1);
    ui->lifesLabel->setText("LIFES: " + QString::number(curLifes));

    pacman->stop();
    ghosts[0]->stop = 1;


    if(curLifes == 0){
        pacman->KeyA = 0;
        ghosts[0]->KeyA = 0;
        die = 1;
        scene->addItem(dl);
        dl->setPos(-300, -300);
        pacman->die();
    }
    else
    foreach (QGraphicsItem *ghost, ghosts)
    {
        ghost->setPos(0, 60);
        pacman->setPos(0, 0);
    }

    scene->update();
}

void Widget::winscene() {

    pacman->stop();
    ghosts[0]->stop = 1;

    pacman->KeyA = 0;
    ghosts[0]->KeyA = 0;
    win = 1;
    scene->addItem(wl);
    wl->setPos(-250, -250);
    pacman->die();
    ui->scorewin->setText("time: " + QString::number(finaltime/5));
    scene->update();

}

void Widget::revive() {
    pacman->go();
    nextlevel(1);
    pacman->KeyA = 1;
    ghosts[0]->KeyA = 1;
    level = 1;
    if(die){
        scene->removeItem(dl);
        die = 0;
    }
    if(win){
        scene->removeItem(wl);
        win = 0;
    }
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    if(die || win)revive();

    if(ev->key() == Qt::Key_P)
        pause();
}
void Widget::nextlevel(int level) {
    pacman->setPos(200, 200);

    if(level == 1){block = block1; finaltime = 0;}
    if(level == 2)block = block2;
    if(level == 3)block = block3;

    foreach(Ghost *ghost, ghosts) {
        scene->removeItem(ghost);
        ghosts.removeOne(ghost);
        delete ghost;
    }

    foreach(QGraphicsItem *piece, pieces) {
        scene->removeItem(piece);
        pieces.removeOne(piece);
        delete piece;
    }

    foreach (QGraphicsItem *wallblock, wallblocks) {
        scene->removeItem(wallblock);
        wallblocks.removeOne(wallblock);
        delete wallblock;
    }

    int x = -240,y = -240;

    bool map[24][24];
    int map_row = 0, map_column = 0;

    for(int i = 0; i < 676; i++){
       if (block[i] == '+'){

           WallBlock *wallblock = new WallBlock();
           scene->addItem(wallblock);
           wallblock->setPos(x, y);
           wallblocks.append(wallblock);
           x += 20;

           map[map_row][map_column] = false;
           map_column++;

       }else if(block[i] == '-') {
           Piece *piece = new Piece();
           scene->addItem(piece);
           piece->setPos(x, y);
           pieces.append(piece);
           x += 20;

           map[map_row][map_column] = true;
           map_column++;

       }else if(block[i] == '.'){
           x += 20;

           map[map_row][map_column] = true;
           map_column++;

       }else if(block[i] == '*'){
           x = -240;
           y += 20;

           map_row++;
           map_column = 0;
        }
    }

    ui->scorewin->setText("");

    ghost = new Ghost();
    ghost->mapInit(map);
    scene->addItem(ghost);
    ghost->setPos(0, 0);
    ghosts.append(ghost);

    ui->scoreLabel->setText("SCORE: 0");
    ui->lifesLabel->setText("LIFES: 3");
}

void Widget::pause(){
    pacman->stop();
    ghosts[0]->stop = 1;
}

