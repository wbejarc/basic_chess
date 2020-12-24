#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // KNIGHT_H
