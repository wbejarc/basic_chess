#ifndef OBJECTITEM_H
#define OBJECTITEM_H

#include <QGraphicsItem>

class StaticItem : public QGraphicsItem
{
public:
    StaticItem(int x, int y, int w, int h, QGraphicsItem *parent = nullptr);
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;

protected:
    int mx, my;
    int mw, mh;

    QRectF boundingRect() const override;
};

#endif // OBJECTITEM_H
