#include "graphicsscene.h"
#include "globaldefines.h"

#include <QtDebug>
#include <QKeyEvent>

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(0.0, 0.0, XSIZE, YSIZE, parent)
{
    createObjects();
    configureObjects();
    connectObjects();
}

void GraphicsScene::startScene()
{
    mThreadTimer->start();
    mChessBoard->playerTurn->setText("Juego iniciado. Turno del jugador blanco.");
}

void GraphicsScene::stopScene()
{
    mThreadTimer->terminate();
}

void GraphicsScene::createObjects()
{
    mThreadTimer = new ThreadTimer(MILISECONDS, this);
    mChessBoard = ChessBoard::getInstance();
}

void GraphicsScene::configureObjects()
{
    mChessBoard->setPos(0,0);
    addItem(mChessBoard);
    //addRect(0.0, 0.0, XSIZE, YSIZE, QPen(QColor(Qt::red)));
}

void GraphicsScene::connectObjects()
{
    connect(mThreadTimer, &ThreadTimer::timeOut, this, &GraphicsScene::updateScene);
}

void GraphicsScene::updateScene()
{
    // la lógica del juego
    mChessBoard->checkMoves();
    mChessBoard->drawPiecePossibleMovements();
    mChessBoard->verifyCheck();
    update();
}

void GraphicsScene::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    //mTileItem->move(event->key());
}

void GraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
}
