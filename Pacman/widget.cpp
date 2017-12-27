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

    scene->addItem(pacman);
    pacman->setPos(0, 0);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, pacman, &PacMan::MoveOnTime);
    timer->start(1000 / 200);

    connect(pacman, &PacMan::signalCheckItem, this, &Widget::stop);
    QFile file(":lvl1");
    //QByteArray block;
    if(!file.open(QIODevice::ReadOnly))
    {qDebug() <<  "Cannot open a file";}else{
       block = file.readAll();
    }
    restart();
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

    pacman->stop();
    ghosts[0]->stop();


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

void Widget::restart() {
    pacman->setPos(0, 0);

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

    ghost = new Ghost();
    scene->addItem(ghost);
    ghost->setPos(0, 60);
    ghosts.append(ghost);

    ui->scoreLabel->setText("SCORE: 0");
    ui->lifesLabel->setText("LIFES: 3");
}

void Widget::revive() {
    pacman->go();
    restart();
    pacman->KeyA = 1;
    ghosts[0]->KeyA = 1;
    if(die){
        scene->removeItem(dl);
        die = 0;
    }
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    if(die)revive();
}
