#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "piece.h"

class AbstractFactory
{
public:
    AbstractFactory();
    virtual Piece* FactoryMethod(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr) const = 0;
};

#endif // ABSTRACTFACTORY_H
