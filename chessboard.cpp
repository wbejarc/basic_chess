#include <vector>
#include <iostream>

#include "chessboard.h"
#include "globaldefines.h"
#include "position.h"

ChessBoard* ChessBoard::instance = nullptr;

ChessBoard* ChessBoard::getInstance(QGraphicsItem *parent)
{
    if (instance == nullptr)
        instance = new ChessBoard(parent);

    return instance;
}

ChessBoard::ChessBoard(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemHasNoContents);

    int mx = 0;
    int my = 0;

    for(unsigned i = 1; i <= TILESCOUNT; i++)
    {
        int x = BORDER;
        int y = BORDER;

        x += WTILE * mx;
        y += HTILE * my;

        unsigned char type = 0;
        if ((mx % 2 == 0 && my % 2 != 0) || (mx % 2 != 0 && my % 2 == 0))
            type = 1;

        TileItem *tile = new TileItem(i, x, y, WTILE, HTILE, type, this);
        tiles.push_back(tile);
        loadPieces(x, y, i, tile);

        mx++;

        if (i % 8 == 0)
        {
            mx = 0;
            my++;
        }
    }

    mx = 0;
    my = 0;

    for(unsigned i = 1; i <= TILESCOUNT / 8; i++)
    {
        int x1 = BORDER / 2 - 4;
        int x2 = BORDER + (BORDER / 2) + 8 * WTILE - 4;

        int y1 = 8 + BORDER / 2 ;
        int y2 = 8 + BORDER / 2 + BORDER + 8 * HTILE;

        int x = BORDER + WTILE / 2 - 6;
        int y = BORDER * 2 + 8;

        x += WTILE * mx;
        y += HTILE * my;

        unsigned char textNumber = 56 - my;
        unsigned char textLetter = 65 + my;

        borderItems.push_back(new BorderItem(x1, y, BORDER, HTILE, textNumber, this));
        borderItems.push_back(new BorderItem(x2, y, BORDER, HTILE, textNumber, this));

        borderItems.push_back(new BorderItem(x, y1, WTILE, BORDER, textLetter, this));
        borderItems.push_back(new BorderItem(x, y2, WTILE, BORDER, textLetter, this));

        mx++;
        my++;
    }

    mx = 0;
    my = 0;

    for(unsigned i = 1; i <= 16; i++)
    {
        int x = BORDER * 3 + WTILE * 8;
        int y = BORDER;

        x += WTILE * mx;
        y += HTILE * my;

        TileItem *tile = new TileItem(i, x, y, WTILE, HTILE, 3, this);
        blackCapturedTiles.push_back(tile);

        my++;

        if (i % 8 == 0)
        {
            my = 0;
            mx++;
        }
    }

    mx = 0;
    my = 0;

    for(unsigned i = 1; i <= 16; i++)
    {
        int x = BORDER * 4 + WTILE * 10;
        int y = BORDER;

        x += WTILE * mx;
        y += HTILE * my;

        TileItem *tile = new TileItem(i, x, y, WTILE, HTILE, 3, this);
        whiteCapturedTiles.push_back(tile);

        my++;

        if (i % 8 == 0)
        {
            my = 0;
            mx++;
        }
    }

    mx = BORDER;
    my = BORDER * 4 + HTILE * 8;

    playerTurn = new Message(mx, my, WTILE * 10, HTILE, this);

    mx = BORDER;
    my = BORDER * 6 + HTILE * 8;

    message = new Message(mx, my, WTILE * 10, HTILE, this);

    mx = BORDER * 5 + WTILE * 12;
    my = BORDER;

    lastMovements = new Message(mx, my, WTILE * 4, HTILE * 8, this);
    lastMovements->setAlign(1);
}

QRectF ChessBoard::boundingRect() const
{
    return QRectF();
}

void ChessBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void ChessBoard::checkMoves()
{
    for (TileItem* tileDropped : tiles)
    {
        if (tileDropped->mDropped)
        {
            for (TileItem* tilePressed : tiles)
            {
                if (tilePressed->mPressed)
                {
                    Piece *piece = tilePressed->mPiece;
                    piece->setPosition(tileDropped->getX(), tileDropped->getY());

                    if (tileDropped->mPiece != nullptr)
                    {
                        Piece *capturedPiece = tileDropped->mPiece;

                        if (capturedPiece->getPieceColor() == WHITE_PIECE)
                        {
                            whitePieces.erase(whitePieces.begin() + capturedPiece->mVectorPosition);

                            // modificar indices de las demas piezas
                            int i = 0;
                            for (Piece* piece : whitePieces)
                            {
                                if (i >= capturedPiece->mVectorPosition)
                                {
                                    piece->mVectorPosition -= 1;
                                }
                                i++;
                            }

                            // tenemos que poner la pieza en las piezas capturadas
                            capturedPiece->mVectorPosition = whiteCapturedPieces.size();
                            TileItem* tile = whiteCapturedTiles[whiteCapturedPieces.size()];
                            capturedPiece->setPosition(tile->getX(), tile->getY());

                            whiteCapturedPieces.push_back(capturedPiece);
                        }
                        else
                        {
                            blackPieces.erase(blackPieces.begin() + capturedPiece->mVectorPosition);
                            // modificar indices de las demas piezas
                            int i = 0;
                            for (Piece* piece : blackPieces)
                            {
                                if (i >= capturedPiece->mVectorPosition)
                                {
                                    piece->mVectorPosition -= 1;
                                }
                                i++;
                            }

                            // tenemos que poner la pieza en las piezas capturadas
                            capturedPiece->mVectorPosition = blackCapturedPieces.size();
                            TileItem* tile = blackCapturedTiles[blackCapturedPieces.size()];
                            capturedPiece->setPosition(tile->getX(), tile->getY());

                            blackCapturedPieces.push_back(capturedPiece);
                        }

                        char mov[4];
                        mov[0] = piece->mId;
                        mov[1] = 'x';
                        mov[3] = 56 - tileDropped->mRow;
                        mov[2] = 97 + tileDropped->mCol;
                        std::string movStr = "";
                        movStr.append(mov, 0, 4);
                        algebraicMovements.push_back(movStr);
                    }
                    else
                    {
                        char mov[3];
                        mov[0] = piece->mId;
                        mov[2] = 56 - tileDropped->mRow;
                        mov[1] = 97 + tileDropped->mCol;
                        std::string movStr = "";
                        movStr.append(mov, 0, 3);
                        algebraicMovements.push_back(movStr);
                    }

                    piece->setTile(tileDropped);
                    tileDropped->setPiece(piece);
                    tilePressed->mPiece = nullptr;

                    tilePressed->mPressed = false;
                    tileDropped->mDropped = false;                    

                    mActualTurn = mActualTurn == WHITE_PLAYER_TURN ? BLACK_PLAYER_TURN : WHITE_PLAYER_TURN;
                    updateChessBoard();

                    if (piece->getPieceType() == PAWN_PIECE && ((Pawn*)piece)->firstMovement)
                    {
                        ((Pawn*)piece)->firstMovement = false;
                    }

                    // almacenar los posibles movimientos de la pieza
                    possibleMovements.clear();
                    possibleMovements = checkPiecePossibleMovements(piece);
                }
            }
        }
    }
}

void ChessBoard::drawPiecePossibleMovements()
{
    for (TileItem* tilePressed : tiles)
    {
        if (tilePressed->mPressed)
        {
            Piece *piece = tilePressed->mPiece;
            PieceColor pieceColor = piece->getPieceColor();

            if (mActualTurn == WHITE_PLAYER_TURN && pieceColor != WHITE_PIECE)
            {
                message->setText("Solo puedes mover tus piezas (BLANCAS).");
                tilePressed->mPressed = false;
                return;
            }

            if (mActualTurn == BLACK_PLAYER_TURN && pieceColor != BLACK_PIECE)
            {
                message->setText("Solo puedes mover tus piezas (NEGRAS).");
                tilePressed->mPressed = false;
                return;
            }

            drawPiecePossibleMovements(piece);
            /*PieceType pieceType = piece->getPieceType();
            int mRow = piece->getTile()->mRow;
            int mCol = piece->getTile()->mCol;            

            if (pieceType == PAWN_PIECE)
                drawPawnPossibleMovements(mRow, mCol, pieceColor, piece);
            else if (pieceType == ROOK_PIECE)
                drawRookPossibleMovements(mRow, mCol, pieceColor);
            else if (pieceType == KNIGHT_PIECE)
                drawKnightPossibleMovements(mRow, mCol, pieceColor);
            else if (pieceType == BISHOP_PIECE)
                drawBishopPossibleMovements(mRow, mCol, pieceColor);
            else if (pieceType == QUEEN_PIECE)
                drawQueenPossibleMovements(mRow, mCol, pieceColor);
            else if (pieceType == KING_PIECE)
                drawKingPossibleMovements(mRow, mCol, pieceColor);*/

        }
    }
}

void ChessBoard::verifyCheck()
{
    std::vector<Piece*> pieces {0};
    if (mActualTurn == WHITE_PLAYER_TURN)
    {
        pieces = whitePieces;
    }
    else
    {
        pieces = blackPieces;
    }

    for (Piece* piece : pieces)
    {
        if (piece->getPieceType() == KING_PIECE)
        {
            TileItem* tile = piece->getTile();

            for (Position position : possibleMovements)
            {
                if (position == Position(tile->mRow, tile->mCol))
                {
                    std::cout << "Jaque" << std::endl;

                    // verificar si el rey tiene movimientos
                    PieceColor color = piece->getPieceColor();
                    std::vector<Position> kingPositions
                            = checkKingPossibleMovements(tile->mRow, tile->mCol, color);

                    bool finded{false};
                    bool possibleCheckMate{true};
                    for (Position kingPosition : kingPositions)
                    {
                        finded = findPosition(kingPosition, possibleMovements);

                        if (!finded)
                        {
                            // TODO Se debe verificar que el movimiento que puede realizar
                            // no tiene amenaza de jaque
                            std::cout << "Jaque - El rey se puede mover" << std::endl;
                            if (mActualTurn == WHITE_PLAYER_TURN)
                                message->setText("El rey del jugador blanco está en jaque.");
                            else
                                message->setText("El rey del jugador negro está en jaque.");
                            possibleCheckMate = false;
                            break;
                        }
                    }

                    if (possibleCheckMate)
                    {
                        // TODO verificar movimientos de piezas aliadas para evitar el jaque
                        std::cout << "Jaque Mate" << std::endl;
                        if (mActualTurn == WHITE_PLAYER_TURN)
                            message->setText("Jaque Mate, el ganador jugador Negro.");
                        else
                            message->setText("Jaque Mate, el ganador jugador Blanco.");
                    }
                }
            }

            return;
        }
    }
}

void ChessBoard::loadPieces(int x, int y, unsigned i, TileItem *tile)
{
    char pieceBoard = initialBoard[i - 1];
    Piece *piece = nullptr;

    int wi = 0;
    int bi = 0;

    switch (pieceBoard)
    {
    case 'p':
        //piece = new Pawn(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::PAWN_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::PAWN_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'P':
        //piece = new Pawn(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::PAWN_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::PAWN_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    case 'r':
        //piece = new Rook(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::ROOK_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::ROOK_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'R':
        //piece = new Rook(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::ROOK_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::ROOK_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    case 'n':
        //piece = new Knight(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::KNIGHT_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::KNIGHT_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'N':
        //piece = new Knight(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::KNIGHT_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::KNIGHT_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    case 'b':
        //piece = new Bishop(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::BISHOP_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::BISHOP_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'B':
        //piece = new Bishop(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::BISHOP_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::BISHOP_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    case 'q':
        //piece = new Queen(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::QUEEN_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::QUEEN_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'Q':
        //piece = new Queen(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::QUEEN_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::QUEEN_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    case 'k':
        //piece = new King(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::KING_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::WHITE_PIECE, PieceType::KING_PIECE, this);
        piece->mVectorPosition = wi; wi++;
        whitePieces.push_back(piece);
        break;
    case 'K':
        //piece = new King(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::KING_PIECE, this);
        piece = factory->FactoryMethod(x, y, WTILE, HTILE, PieceColor::BLACK_PIECE, PieceType::KING_PIECE, this);
        piece->mVectorPosition = bi; bi++;
        blackPieces.push_back(piece);
        break;
    }

    if (piece != nullptr)
    {
        tile->setPiece(piece);
        piece->setTile(tile);
        piece->setFunction(std::bind(&ChessBoard::updateChessBoard, this));
    }
}

void ChessBoard::updateChessBoard()
{
    for(TileItem* tile : tiles)
    {
        tile->mPressed = false;
        tile->mAvailable = false;
        tile->mTaken = false;
    }

    message->setText("-");

    if (mActualTurn == WHITE_PLAYER_TURN)
        playerTurn->setText("Turno del jugador blanco.");
    else
        playerTurn->setText("Turno del jugador negro.");

    std::string movements;
    if (algebraicMovements.size() > 20)
    {
        int n = 20;
        std::vector<std::string> last20Slice(algebraicMovements.end() - n, algebraicMovements.end());
        int i = 0;
        for (std::string text : last20Slice)
        {
            movements += text + " ";
            i++;
            if (i % 2 == 0)
            {
                i = 0;
                movements += "\n";
            }
        }
    }
    else
    {
        int i = 0;
        for (std::string text : algebraicMovements)
        {
            movements += text + " ";
            i++;
            if (i % 2 == 0)
            {
                i = 0;
                movements += "\n";
            }
        }
    }

    lastMovements->setText(movements);
}

void ChessBoard::drawPiecePossibleMovements(Piece *piece)
{
    std::vector<Position> positions = checkPiecePossibleMovements(piece);

    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;

        if (pos.IsTaken())
            tiles[m]->mTaken = true;
    }
}

std::vector<Position> ChessBoard::checkPiecePossibleMovements(Piece* piece)
{
    std::vector<Position> positions;

    PieceColor pieceColor = piece->getPieceColor();
    PieceType pieceType = piece->getPieceType();
    int mRow = piece->getTile()->mRow;
    int mCol = piece->getTile()->mCol;

    switch (pieceType) {
    case PAWN_PIECE:
        positions = checkPawnPossibleMovements(mRow, mCol, pieceColor, piece);
        break;
    case ROOK_PIECE:
        positions = checkRookPossibleMovements(mRow, mCol, pieceColor);
        break;
    case KNIGHT_PIECE:
        positions = checkKnightPossibleMovements(mRow, mCol, pieceColor);
        break;
    case BISHOP_PIECE:
        positions = checkBishopPossibleMovements(mRow, mCol, pieceColor);
        break;
    case QUEEN_PIECE:
        positions = checkQueenPossibleMovements(mRow, mCol, pieceColor);
        break;
    case KING_PIECE:
        positions = checkKingPossibleMovements(mRow, mCol, pieceColor);
        break;
    }

    return positions;
}

void ChessBoard::drawPawnPossibleMovements(int mRow, int mCol, PieceColor color, Piece* piece)
{
    std::vector<Position> positions = checkPawnPossibleMovements(mRow, mCol, color, piece);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkPawnPossibleMovements(int mRow, int mCol, PieceColor color, Piece* piece)
{
    std::vector<Position> positions{0};

    int factor = 1;
    if (color == WHITE_PIECE)
        factor = -1;

    bool canMove = false;

    int mv = (mRow + (1 * factor)) * 8 + mCol;
    if (tiles[mv]->mPiece == nullptr)
    {
        positions.push_back(Position(mRow + (1 * factor), mCol));
        canMove = true;
    }

    if (((Pawn*) piece)->firstMovement && canMove)
    {
        int mvi = (mRow + (2 * factor)) * 8 + mCol;
        if (tiles[mvi]->mPiece == nullptr)
        {
            positions.push_back(Position(mRow + (2 * factor), mCol));
        }
    }

    int mci = (mRow + (1 * factor)) * 8 + (mCol - 1);
    int mcd = (mRow + (1 * factor)) * 8 + (mCol + 1);
    if (tiles[mci]->mPiece != nullptr && tiles[mci]->mPiece->getPieceColor() != color)
    {
        Position position(mRow + (1 * factor), mCol - 1);
        position.SetTaken(true);
        position.SetColor(color);
        positions.push_back(position);
    }
    if (tiles[mcd]->mPiece != nullptr && tiles[mcd]->mPiece->getPieceColor() != color)
    {
        Position position(mRow + (1 * factor), mCol + 1);
        position.SetTaken(true);
        position.SetColor(color);
        positions.push_back(position);
    }

    return positions;
}

void ChessBoard::drawRookPossibleMovements(int mRow, int mCol, PieceColor color)
{
    /*bool canMoveV1 = true;
    bool canMoveV2 = true;
    bool canMoveH1 = true;
    bool canMoveH2 = true;

    for (int i = 1; i <= 8; i++)
    {
        if (canMoveV1)
            canMoveV1 = checkRookMovement(mRow, mCol - i, color);
        if (canMoveV2)
            canMoveV2 = checkRookMovement(mRow, mCol + i, color);
        if (canMoveH1)
            canMoveH1 = checkRookMovement(mRow - i, mCol, color);
        if (canMoveH2)
            canMoveH2 = checkRookMovement(mRow + i, mCol, color);
    }*/
    std::vector<Position> positions = checkRookPossibleMovements(mRow, mCol, color);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkRookPossibleMovements(int mRow, int mCol, PieceColor color)
{
    std::vector<Position> positions{0};

    bool canMoveV1 = true;
    bool canMoveV2 = true;
    bool canMoveH1 = true;
    bool canMoveH2 = true;

    for (int i = 1; i <= 8; i++)
    {
        if (canMoveV1)
            canMoveV1 = checkRookMovement(Position(mRow, mCol - i), color, positions);
        if (canMoveV2)
            canMoveV2 = checkRookMovement(Position(mRow, mCol + i), color, positions);
        if (canMoveH1)
            canMoveH1 = checkRookMovement(Position(mRow - i, mCol), color, positions);
        if (canMoveH2)
            canMoveH2 = checkRookMovement(Position(mRow + i, mCol), color, positions);
    }

    return positions;
}

bool ChessBoard::checkRookMovement(Position position, PieceColor color, std::vector<Position> &positions)
{
    if (position.GetX() >= 0 && position.GetX() <= 7 && position.GetY() >= 0 && position.GetY() <= 7)
    {
        int m = position.GetX() * 8 + position.GetY();

        if (tiles[m]->mPiece == nullptr)
        {
            positions.push_back(position);
            return true;
        }
        else
        {
            PieceColor colorTaken = tiles[m]->mPiece->getPieceColor();
            if (colorTaken != color)
            {
                position.SetTaken(true);
                position.SetColor(colorTaken);
                positions.push_back(position);
            }

            return false;
        }
    }
    return false;
}

bool ChessBoard::checkRookMovement(int mRow, int mCol, PieceColor color)
{
    if (mRow >= 0 && mRow <= 7 && mCol >= 0 && mCol <= 7)
    {
        int m = mRow * 8 + mCol;

        if (tiles[m]->mPiece == nullptr)
        {
            tiles[m]->mAvailable = true;
            return true;
        }
        else
        {
            if (tiles[m]->mPiece->getPieceColor() != color)
                tiles[m]->mAvailable = true;
            return false;
        }
    }
    return false;
}

void ChessBoard::drawKnightPossibleMovements(int mRow, int mCol, PieceColor color)
{
    /*int mRow1 = mRow + 2;
    int mRow2 = mRow - 2;
    int mRow3 = mRow + 1;
    int mRow4 = mRow - 1;

    int mCol1 = mCol - 1;
    int mCol2 = mCol + 1;
    int mCol3 = mCol - 2;
    int mCol4 = mCol + 2;

    checkKnightMovement(mRow1, mCol1, color);
    checkKnightMovement(mRow1, mCol2, color);
    checkKnightMovement(mRow2, mCol1, color);
    checkKnightMovement(mRow2, mCol2, color);
    checkKnightMovement(mRow3, mCol3, color);
    checkKnightMovement(mRow3, mCol4, color);
    checkKnightMovement(mRow4, mCol3, color);
    checkKnightMovement(mRow4, mCol4, color);*/

    std::vector<Position> positions = checkKnightPossibleMovements(mRow, mCol, color);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkKnightPossibleMovements(int mRow, int mCol, PieceColor color)
{
    std::vector<Position> positions{0};

    checkKnightMovement(Position(mRow + 2, mCol - 1), color, positions);
    checkKnightMovement(Position(mRow + 2, mCol + 1), color, positions);
    checkKnightMovement(Position(mRow - 2, mCol - 1), color, positions);
    checkKnightMovement(Position(mRow - 2, mCol + 1), color, positions);
    checkKnightMovement(Position(mRow + 1, mCol - 2), color, positions);
    checkKnightMovement(Position(mRow + 1, mCol + 2), color, positions);
    checkKnightMovement(Position(mRow - 1, mCol - 2), color, positions);
    checkKnightMovement(Position(mRow - 1, mCol + 2), color, positions);

    return positions;
}

void ChessBoard::checkKnightMovement(Position position, PieceColor color, std::vector<Position> &positions)
{
    if (position.GetX() >= 0 && position.GetX() <= 7 && position.GetY() >= 0 && position.GetY() <= 7)
    {
        int m = position.GetX() * 8 + position.GetY();

        if (tiles[m]->mPiece == nullptr)
        {
            positions.push_back(position);
        }
        else
        {
            PieceColor colorTaken = tiles[m]->mPiece->getPieceColor();
            if (colorTaken != color)
            {
                position.SetTaken(true);
                position.SetColor(colorTaken);
                positions.push_back(position);
            }
        }
    }
}

void ChessBoard::checkKnightMovement(int mRow, int mCol, PieceColor color)
{
    if (mRow >= 0 && mRow <= 7 && mCol >= 0 && mCol <= 7)
    {
        int m = mRow * 8 + mCol;

        if (tiles[m]->mPiece == nullptr)
            tiles[m]->mAvailable = true;
        else
        {
            if (tiles[m]->mPiece->getPieceColor() != color)
                tiles[m]->mAvailable = true;
        }
    }
}

void ChessBoard::drawBishopPossibleMovements(int mRow, int mCol, PieceColor color)
{
    /*bool canMoveD1 = true;
    bool canMoveD2 = true;
    bool canMoveD3 = true;
    bool canMoveD4 = true;

    for (int i = 1; i <= 8; i++)
    {
        if (canMoveD1)
            canMoveD1 = checkBishopMovement(mRow - i, mCol - i, color);
        if (canMoveD2)
            canMoveD2 = checkBishopMovement(mRow - i, mCol + i, color);
        if (canMoveD3)
            canMoveD3 = checkBishopMovement(mRow + i, mCol - i, color);
        if (canMoveD4)
            canMoveD4 = checkBishopMovement(mRow + i, mCol + i, color);
    }*/
    std::vector<Position> positions = checkBishopPossibleMovements(mRow, mCol, color);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkBishopPossibleMovements(int mRow, int mCol, PieceColor color)
{
    std::vector<Position> positions{0};

    bool canMoveD1 = true;
    bool canMoveD2 = true;
    bool canMoveD3 = true;
    bool canMoveD4 = true;

    for (int i = 1; i <= 8; i++)
    {
        if (canMoveD1)
            canMoveD1 = checkBishopMovement(Position(mRow - i, mCol - i), color, positions);
        if (canMoveD2)
            canMoveD2 = checkBishopMovement(Position(mRow - i, mCol + i), color, positions);
        if (canMoveD3)
            canMoveD3 = checkBishopMovement(Position(mRow + i, mCol - i), color, positions);
        if (canMoveD4)
            canMoveD4 = checkBishopMovement(Position(mRow + i, mCol + i), color, positions);
    }

    return positions;
}

bool ChessBoard::checkBishopMovement(Position position, PieceColor color, std::vector<Position> &positions)
{
    if (position.GetX() >= 0 && position.GetX() <= 7 && position.GetY() >= 0 && position.GetY() <= 7)
    {
        int m = position.GetX() * 8 + position.GetY();

        if (tiles[m]->mPiece == nullptr)
        {
            positions.push_back(position);
            return true;
        }
        else
        {
            PieceColor colorTaken = tiles[m]->mPiece->getPieceColor();
            if (colorTaken != color)
            {
                position.SetTaken(true);
                position.SetColor(colorTaken);
                positions.push_back(position);
            }

            return false;
        }
    }
    return false;
}

bool ChessBoard::checkBishopMovement(int mRow, int mCol, PieceColor color)
{
    if (mRow >= 0 && mRow <= 7 && mCol >= 0 && mCol <= 7)
    {
        int m = mRow * 8 + mCol;

        if (tiles[m]->mPiece == nullptr)
        {
            tiles[m]->mAvailable = true;
            return true;
        }
        else
        {
            if (tiles[m]->mPiece->getPieceColor() != color)
                tiles[m]->mAvailable = true;
            return false;
        }
    }
    return false;
}

void ChessBoard::drawQueenPossibleMovements(int mRow, int mCol, PieceColor color)
{
    /*drawBishopPossibleMovements(mRow, mCol, color);
    drawRookPossibleMovements(mRow, mCol, color);*/
    std::vector<Position> positions = checkQueenPossibleMovements(mRow, mCol, color);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkQueenPossibleMovements(int mRow, int mCol, PieceColor color)
{
    std::vector<Position> positions{0};

    std::vector<Position> bishopMovements = checkBishopPossibleMovements(mRow, mCol, color);
    std::vector<Position> rookMovements = checkRookPossibleMovements(mRow, mCol, color);

    positions.insert(std::end(positions), std::begin(bishopMovements), std::end(bishopMovements));
    positions.insert(std::end(positions), std::begin(rookMovements), std::end(rookMovements));

    return positions;
}

void ChessBoard::drawKingPossibleMovements(int mRow, int mCol, PieceColor color)
{
    /*checkKingMovement(mRow - 1, mCol, color);
    checkKingMovement(mRow + 1, mCol, color);
    checkKingMovement(mRow, mCol - 1, color);
    checkKingMovement(mRow, mCol + 1, color);
    checkKingMovement(mRow - 1, mCol - 1, color);
    checkKingMovement(mRow - 1, mCol + 1, color);
    checkKingMovement(mRow + 1, mCol - 1, color);
    checkKingMovement(mRow + 1, mCol + 1, color);*/

    std::vector<Position> positions = checkKingPossibleMovements(mRow, mCol, color);
    for(Position pos : positions)
    {
        int m = pos.GetX() * 8 + pos.GetY();
        tiles[m]->mAvailable = true;
    }
}

std::vector<Position> ChessBoard::checkKingPossibleMovements(int mRow, int mCol, PieceColor color)
{
    std::vector<Position> positions{0};

    checkKingMovement(Position(mRow - 1, mCol), color, positions);
    checkKingMovement(Position(mRow + 1, mCol), color, positions);
    checkKingMovement(Position(mRow, mCol - 1), color, positions);
    checkKingMovement(Position(mRow, mCol + 1), color, positions);
    checkKingMovement(Position(mRow - 1, mCol - 1), color, positions);
    checkKingMovement(Position(mRow - 1, mCol + 1), color, positions);
    checkKingMovement(Position(mRow + 1, mCol - 1), color, positions);
    checkKingMovement(Position(mRow + 1, mCol + 1), color, positions);

    return positions;
}

void ChessBoard::checkKingMovement(Position position, PieceColor color, std::vector<Position> &positions)
{
    if (position.GetX() >= 0 && position.GetX() <= 7 && position.GetY() >= 0 && position.GetY() <= 7)
    {
        int m = position.GetX() * 8 + position.GetY();

        if (tiles[m]->mPiece == nullptr)
        {
            positions.push_back(position);
        }
        else
        {
            PieceColor colorTaken = tiles[m]->mPiece->getPieceColor();
            if (colorTaken != color)
            {
                position.SetTaken(true);
                position.SetColor(colorTaken);
                positions.push_back(position);
            }
        }
    }
}

void ChessBoard::checkKingMovement(int mRow, int mCol, PieceColor color)
{
    if (mRow >= 0 && mRow <= 7 && mCol >= 0 && mCol <= 7)
    {
        int m = mRow * 8 + mCol;

        if (tiles[m]->mPiece == nullptr)
            tiles[m]->mAvailable = true;
        else
        {
            if (tiles[m]->mPiece->getPieceColor() != color)
                tiles[m]->mAvailable = true;
        }
    }
}

bool ChessBoard::findPosition(Position position, const std::vector<Position> &positions)
{
    for (Position pos : positions)
    {
        if (position == pos)
            return true;
    }
    return false;
}
