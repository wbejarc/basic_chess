#include "piece.h"
#include <QApplication>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include "tileitem.h"

Piece::Piece(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent)
    : PressableItem(x, y, w, h, parent), pieceColor{color}, pieceType{pieceType}, tile{nullptr}
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void Piece::setTile(TileItem *tile)
{
    this->tile = tile;
}

void Piece::setFunction(std::function<void(void)> function)
{
    mFunction = function;
}

PieceColor Piece::getPieceColor()
{
    return pieceColor;
}

PieceType Piece::getPieceType()
{
    return pieceType;
}

TileItem *Piece::getTile()
{
    return tile;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    std::cout << tile->mRow << "," << tile->mCol << std::endl;
    setCursor(Qt::ClosedHandCursor);
    mFunction();
    tile->mPressed = true;
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->scenePos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance())
    {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData();
    mime->setText(QString("Drag&Drop"));
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}
