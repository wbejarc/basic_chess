#include "borderitem.h"
#include <QPainter>

BorderItem::BorderItem(int x, int y, int w, int h, unsigned char text, QGraphicsItem *parent)
    : StaticItem(x, y, w, h, parent), mText{text}
{
}

void BorderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setFont(QFont("Times", 16, QFont::Bold));
    painter->drawText(QPoint(mx, my), QString(QChar(mText)));
}
