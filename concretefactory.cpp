#include "concretefactory.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

ConcreteFactory::ConcreteFactory()
{    
}

Piece *ConcreteFactory::FactoryMethod(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent) const
{
    switch (pieceType)
    {
    case PAWN_PIECE:
        return new Pawn(x, y, w, h, color, PAWN_PIECE, parent);
        break;
    case ROOK_PIECE:
        return new Rook(x, y, w, h, color, ROOK_PIECE, parent);
        break;
    case KNIGHT_PIECE:
        return new Knight(x, y, w, h, color, KNIGHT_PIECE, parent);
        break;
    case BISHOP_PIECE:
        return new Bishop(x, y, w, h, color, BISHOP_PIECE, parent);
        break;
    case QUEEN_PIECE:
        return new Queen(x, y, w, h, color, QUEEN_PIECE, parent);
        break;
    case KING_PIECE:
        return new King(x, y, w, h, color, KING_PIECE, parent);
        break;
    }

    return nullptr;
}
