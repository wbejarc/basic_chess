#include "tileitem.h"
#include "globaldefines.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <cmath>
#include <iostream>

TileItem::TileItem(unsigned i, int x, int y, int w, int h, unsigned char type, QGraphicsItem *parent)
    : StaticItem(x, y, w, h, parent), mPiece{nullptr}
{
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    mRow = std::floor((i - 1) / 8);
    mCol = (i - 1) % 8;
    mType = type;
    mVectorPos = i - 1;
}

void TileItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    mHover = true;
}

void TileItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    mHover = false;
}

void TileItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText() && mAvailable)
    {
        event->setAccepted(true);
        mDragOver = true;
        update();
    }
    else
    {
        event->setAccepted(false);
    }
}

void TileItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    mDragOver = false;
    update();
}

void TileItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    mDragOver = false;
    if (event->mimeData()->hasText())
    {
        mDropped = true;
    }
    update();
}

void TileItem::setPiece(Piece *piece)
{
    mPiece = piece;
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    pen.setWidth(2);

    if (mHover && !mPressed)
    {
        pen.setBrush(Qt::red);
        setZValue(500);
    }
    else if (mPressed)
    {
        pen.setBrush(Qt::green);
        setZValue(501);
    }
    else if (mAvailable)
    {
        pen.setBrush(Qt::blue);
        setZValue(500);
    }    
    else
    {
        pen.setBrush(Qt::black);
        setZValue(0);
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    QPainterPath path;
    path.addRect(mx, my, mw, mh);

    if (mTaken)
        painter->fillPath(path, QBrush(QColor(255, 168, 168)));
    else if (mAvailable)
        painter->fillPath(path, QBrush(QColor(225, 236, 244)));
    else if (mPressed)
        painter->fillPath(path, QBrush(QColor(185, 255, 168)));
    else if (mType == 0)
        painter->fillPath(path, QBrush(QColor(255, 255, 255)));
    else if (mType == 1)
        painter->fillPath(path, QBrush(QColor(225, 214, 125)));
    else
        painter->fillPath(path, QBrush(QColor(240, 240, 240)));

    painter->drawPath(path);
}
