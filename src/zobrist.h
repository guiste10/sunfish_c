#ifndef SUNFISH_C_ZOBRIST_H
#define SUNFISH_C_ZOBRIST_H
#include "position.h"
#define NUM_CASTLING_SIDES 2
#define NUM_FILES 10

extern uint64_t blackToMoveHash;
extern uint64_t castlingRightsHash[NUM_COLORS][NUM_CASTLING_SIDES];
extern uint64_t enPassantFileHash[NUM_FILES];
extern uint64_t pieceHashForSquares[NUM_PIECES][SIZE];
void setInitialZobristHash(Position* position);
#endif //SUNFISH_C_ZOBRIST_H
