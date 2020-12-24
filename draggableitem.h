#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H

#include <QGraphicsItem>

class DraggableItem : public QGraphicsItem
{
public:
    DraggableItem(QGraphicsItem *parent = nullptr);

/*protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    bool dragOver = false;*/
};

#endif // DRAGGABLEITEM_H
