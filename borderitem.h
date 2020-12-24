#ifndef BORDERITEM_H
#define BORDERITEM_H

#include "staticitem.h"

class BorderItem : public StaticItem
{
public:
    BorderItem(int x, int y, int w, int h, unsigned char text, QGraphicsItem *parent = nullptr);

protected:
    unsigned char mText;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) override;
};

#endif // BORDERITEM_H
