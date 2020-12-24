#include "pawn.h"
#include <QPainter>

Pawn::Pawn(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent)
    : Piece(x, y, w, h, color, pieceType, parent)
{
    mId = 'P';
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    setZValue(600);

    painter->setFont(QFont("Times", 28, QFont::Normal));

    if (pieceColor == PieceColor::WHITE_PIECE)
    {
        painter->drawText(QPoint(mx + 5, my + HTILE - 10), QString(QChar(0x2659)));
    }
    else
    {
        painter->drawText(QPoint(mx + 5, my + HTILE - 10), QString(QChar(0x265F)));
    }
}
