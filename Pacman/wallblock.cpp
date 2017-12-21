#include "wallblock.h"

WallBlock::WallBlock(QObject *parent):QObject(parent), QGraphicsItem()
{

}

WallBlock::~WallBlock()
{

}

QRectF WallBlock::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void WallBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(-10, -10, 20, 20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
