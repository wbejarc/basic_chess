#include "queen.h"
#include <QPainter>

Queen::Queen(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent)
    : Piece(x, y, w, h, color, pieceType, parent)
{
    mId = 'Q';
}

void Queen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    setZValue(600);

    painter->setFont(QFont("Times", 28, QFont::Normal));

    if (pieceColor == PieceColor::WHITE_PIECE)
    {
        painter->drawText(QPoint(mx + 5, my + HTILE - 10), QString(QChar(0x2655)));
    }
    else
    {
        painter->drawText(QPoint(mx + 5, my + HTILE - 10), QString(QChar(0x265B)));
    }
}
