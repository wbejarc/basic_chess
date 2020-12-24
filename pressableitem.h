#ifndef PRESSABLEITEM_H
#define PRESSABLEITEM_H

#include "staticitem.h"

class PressableItem : public StaticItem
{
public:
    PressableItem(int x, int y, int w, int h, QGraphicsItem *parent = nullptr);
    bool isPressed = false;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override = 0;

};

#endif // PRESSABLEITEM_H
