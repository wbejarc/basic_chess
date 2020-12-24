#ifndef PIECE_H
#define PIECE_H

#include "globaldefines.h"
#include "pressableitem.h"

class TileItem;

class Piece : public PressableItem
{
public:
    Piece(int x, int y, int w, int h, PieceColor color, PieceType pieceType, QGraphicsItem *parent = nullptr);
    void setTile(TileItem *tile);
    void setFunction(std::function<void(void)> function);
    PieceColor getPieceColor();
    PieceType getPieceType();
    TileItem *getTile();
    int mVectorPosition;
    char mId;

protected:
    PieceColor pieceColor;
    PieceType pieceType;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) override = 0;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    TileItem *tile;
    std::function<void(void)> mFunction;
};

#endif // PIECE_H
