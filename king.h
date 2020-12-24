#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(int x, int y, int w, int h, PieceColor pieceColor, PieceType pieceType, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // KING_H
