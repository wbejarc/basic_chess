#ifndef TILEITEM_H
#define TILEITEM_H

#include "staticitem.h"
#include "piece.h"

class TileItem : public StaticItem
{
public:
    TileItem(unsigned i, int x, int y, int w, int h, unsigned char type, QGraphicsItem *parent = nullptr);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    void setPiece(Piece *piece);
    Piece *mPiece;
    unsigned mRow;
    unsigned mCol;
    bool mPressed {false};
    bool mDragOver {false};
    bool mDropped {false};
    bool mAvailable {false};
    bool mTaken {false};
    int mVectorPos;

protected:
    unsigned char mType;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) override;    

private:
    bool mHover {false};

};

#endif // BALLITEM_H
