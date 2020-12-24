#ifndef POSITION_H
#define POSITION_H

#include "globaldefines.h"

class Position
{
public:
    Position(){}
    Position(unsigned x, unsigned y)
        : mX{x}, mY{y} {}

    const unsigned& GetX()
    {
        return mX;
    }

    const unsigned& GetY()
    {
        return mY;
    }

    void SetPosition(const unsigned& x, const unsigned& y)
    {
        mX = x;
        mY = y;
    }

    void SetTaken(const bool& taken)
    {
        mTaken = taken;
    }

    const bool& IsTaken()
    {
        return mTaken;
    }

    void SetColor(PieceColor& color)
    {
        mColor = color;
    }

    const PieceColor& GetColor()
    {
        return mColor;
    }

    friend bool operator== (const Position& a, const Position& b)
    {
        return (a.mX != b.mX) ? false : (a.mY != b.mY) ? false : true;
    }

    friend bool operator!= (const Position& a, const Position& b)
    {
        return !(a == b);
    }

private:
    unsigned mX {0};
    unsigned mY {0};
    bool mTaken {false};
    PieceColor mColor;
};

#endif // POSITION_H
