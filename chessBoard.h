//
// Created by neiringu on 21-05-23.
//

#ifndef SUNFISH_C_CHESSBOARD_H
#define SUNFISH_C_CHESSBOARD_H

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

const char PIECES[] = "PNBRQK";
const int NUM_PIECES = 6;
const char PROMOTIONS[] = "NBRQ";
const int NUM_PROMOTIONS = 4;

extern const int DIRECTIONS[NUM_PIECES][9];

extern const char initialBoard[];

void copyBoard(char* dest, const char* src);
#endif //SUNFISH_C_CHESSBOARD_H
