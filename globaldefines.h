#ifndef GLOBALDEFINES_H
#define GLOBALDEFINES_H

enum PieceColor
{
  WHITE_PIECE = 0,
  BLACK_PIECE = 1
};

enum PieceType
{
    PAWN_PIECE = 0,
    ROOK_PIECE = 1,
    BISHOP_PIECE = 2,
    KNIGHT_PIECE = 3,
    KING_PIECE = 4,
    QUEEN_PIECE = 5,
};

enum PlayerTurn
{
    WHITE_PLAYER_TURN = 0,
    BLACK_PLAYER_TURN = 1,
};

#define XSIZE 1200.0
#define YSIZE 800.0

#define XBOARD XSIZE/3
#define YBOARD 80
#define TILESCOUNT 64

#define WTILE 60
#define HTILE 60
#define BORDER 30

#define MILISECONDS 10

#endif // GLOBALDEFINES_H
