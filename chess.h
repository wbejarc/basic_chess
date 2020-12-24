#ifndef CHESS_H
#define CHESS_H

#include <QObject>
#include <QGraphicsView>

#include "graphicsscene.h"

class Chess : public QObject
{    
public:
    Chess(QGraphicsView *graphicsView, QObject *parent = nullptr);
    void startGame();
    void stopGame();

private:    
    GraphicsScene *mScene;
};

#endif // CHESS_H
