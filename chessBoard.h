#ifndef SUNFISH_C_CHESSBOARD_H
#define SUNFISH_C_CHESSBOARD_H
#include "constants.h"

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

extern const char PIECES[];
extern const char PROMOTIONS[];
extern const int DIRECTIONS[NUM_PIECES][9];

extern const char initialBoard[];

int getPieceIndex(char piece);

void copyBoard(char* dest, const char* src);
#endif //SUNFISH_C_CHESSBOARD_H
