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

extern const int P;
extern const int N;
extern const int B;
extern const int R;
extern const int Q;
extern const int K;

extern int PIECE_INDEXES_IGNORE_COLOR[PIECES_MAX_ASCII];
extern const char PIECES[];
extern const int DIRECTIONS[NUM_WHITE_PIECES][9];

extern const char initialBoard[];

void initializePieceIndexArray();
void copyBoard(char* dest, const char* src);

#endif //SUNFISH_C_CHESSBOARD_H
