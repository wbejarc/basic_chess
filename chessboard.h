#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>
#include <string>
#include "message.h"
#include "borderitem.h"
#include "tileitem.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "abstractfactory.h"
#include "concretefactory.h"
#include "position.h"

class ChessBoard : public QGraphicsItem
{
public:
    static ChessBoard *getInstance(QGraphicsItem *parent = nullptr);

    std::vector<TileItem*> tiles;
    std::vector<BorderItem*> borderItems;

    std::vector<Piece*> whitePieces;
    std::vector<Piece*> blackPieces;

    std::vector<Piece*> blackCapturedPieces;
    std::vector<TileItem*> blackCapturedTiles;

    std::vector<Piece*> whiteCapturedPieces;
    std::vector<TileItem*> whiteCapturedTiles;

    std::vector<Position> possibleMovements;
    std::vector<std::string> algebraicMovements;

    Message* playerTurn;
    Message* message;
    Message* lastMovements;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Piezas en mayúsculas son negras
    const char initialBoard[64] =
    {
       'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R',
       'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',
       '-',  '-',  '-',  '-',  '-',  '-',  '-',  '-',
       '-',  '-',  '-',  '-',  '-',  '-',  '-',  '-',
       '-',  '-',  '-',  '-',  '-',  '-',  '-',  '-',
       '-',  '-',  '-',  '-',  '-',  '-',  '-',  '-',
       'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p',
       'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r',
    };

    void checkMoves();
    void drawPiecePossibleMovements();
    void verifyCheck();

protected:
    ChessBoard(QGraphicsItem *parent);
    ChessBoard() = delete;
    ChessBoard(ChessBoard const&) = delete;
    ChessBoard& operator=(ChessBoard const&) = delete;
    virtual ~ChessBoard(){}

private:
    static ChessBoard *instance;
    AbstractFactory* factory = new ConcreteFactory();

    void loadPieces(int x, int y, unsigned i, TileItem *tile);
    void updateChessBoard();

    PlayerTurn mActualTurn {WHITE_PLAYER_TURN};
    bool mIsGameEnded {false};

    void drawPiecePossibleMovements(Piece* piece);
    std::vector<Position> checkPiecePossibleMovements(Piece* piece);

    void drawPawnPossibleMovements(int mRow, int mCol, PieceColor color, Piece* piece);
    std::vector<Position> checkPawnPossibleMovements(int mRow, int mCol, PieceColor color, Piece* piece);

    void drawRookPossibleMovements(int mRow, int mCol, PieceColor color);
    std::vector<Position> checkRookPossibleMovements(int mRow, int mCol, PieceColor color);
    bool checkRookMovement(Position position, PieceColor color, std::vector<Position>& positions);
    bool checkRookMovement(int mRow, int mCol, PieceColor color);

    void drawKnightPossibleMovements(int mRow, int mCol, PieceColor color);
    std::vector<Position> checkKnightPossibleMovements(int mRow, int mCol, PieceColor color);
    void checkKnightMovement(Position position, PieceColor color, std::vector<Position>& positions);
    void checkKnightMovement(int mRow, int mCol, PieceColor color);

    void drawBishopPossibleMovements(int mRow, int mCol, PieceColor color);
    std::vector<Position> checkBishopPossibleMovements(int mRow, int mCol, PieceColor color);
    bool checkBishopMovement(Position position, PieceColor color, std::vector<Position>& positions);
    bool checkBishopMovement(int mRow, int mCol, PieceColor color);

    void drawQueenPossibleMovements(int mRow, int mCol, PieceColor color);
    std::vector<Position> checkQueenPossibleMovements(int mRow, int mCol, PieceColor color);

    void drawKingPossibleMovements(int mRow, int mCol, PieceColor color);
    std::vector<Position> checkKingPossibleMovements(int mRow, int mCol, PieceColor color);
    void checkKingMovement(Position position, PieceColor color, std::vector<Position>& positions);
    void checkKingMovement(int mRow, int mCol, PieceColor color);

    bool findPosition(Position position, const std::vector<Position>& positions);
};

#endif // CHESSBOARD_H
