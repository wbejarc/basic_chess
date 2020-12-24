#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // ROOK_H
