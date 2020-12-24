#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(int x, int y, int w, int h, PieceColor pieceColor, PieceType pieceType, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // BISHOP_H
