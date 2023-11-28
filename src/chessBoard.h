#ifndef SUNFISH_C_CHESSBOARD_H
#define SUNFISH_C_CHESSBOARD_H
#include "constants.h"
#define PIECES_MAX_ASCII 115
extern const int A1;
extern const int H1;
extern const int A8;
extern const int H8;

extern const int NORTH;
extern const int EAST;
extern const int SOUTH;
extern const int WEST;

extern const int NORTHNORTH;
extern const int SOUTHSOUTH;

extern const int NORTHWEST;
extern const int NORTHEAST;
extern const int SOUTHWEST;
extern const int SOUTHEAST;

extern const int SPACE;
extern const int EMPTY_SQUARE;

extern const int P;
extern const int N;
extern const int B;
extern const int R;
extern const int Q;
extern const int K;

extern const int p;
extern const int n;
extern const int b;
extern const int r;
extern const int q;
extern const int k;

extern const char ALL_PIECES[NUM_PIECES];
extern const int DIRECTIONS[NUM_PIECES][9];
extern const int initialBoard[];

void initializePieceIndexArray();
void copyBoard(int* dest, const int* src);
#endif //SUNFISH_C_CHESSBOARD_H
