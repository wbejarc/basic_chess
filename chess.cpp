#include "chess.h"

Chess::Chess(QGraphicsView *graphicsView, QObject *parent)
    : QObject(parent)
{
    mScene = new GraphicsScene(this);
    graphicsView->setScene(mScene);
}

void Chess::startGame()
{
    mScene->startScene();
}

void Chess::stopGame()
{
    mScene->stopScene();
}
