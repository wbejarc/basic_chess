#include "staticitem.h"

StaticItem::StaticItem(int x, int y, int w, int h, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    mx = x;
    my = y;
    mw = w;
    mh = h;
}

void StaticItem::setPosition(int x, int y)
{
    mx = x;
    my = y;
}

int StaticItem::getX() const
{
    return mx;
}

int StaticItem::getY() const
{
    return my;
}

QRectF StaticItem::boundingRect() const
{
    return QRectF(mx, my, mw, mh);
}
