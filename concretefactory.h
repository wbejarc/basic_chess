#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "abstractfactory.h"

class ConcreteFactory : public AbstractFactory
{
public:
    ConcreteFactory();
    Piece* FactoryMethod(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr) const override;
};

#endif // CONCRETEFACTORY_H
