#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr);
    bool firstMovement {true};

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // PAWN_H
