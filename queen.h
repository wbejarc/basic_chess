#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(int x, int y, int w, int h, PieceColor pieceColor, PieceType pieceType, QGraphicsItem *parent = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = 0) override;
};

#endif // QUEEN_H
