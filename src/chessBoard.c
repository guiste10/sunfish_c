#include <string.h>
#include "constants.h"
#include "chessBoard.h"

const int A1 = 91;
const int H1 = 98;
const int A8 = 21;
const int H8 = 28;

const int NORTH = -10;
const int EAST = 1;
const int SOUTH = 10;
const int WEST = -1;

const int NORTHNORTH = NORTH + NORTH;
const int SOUTHSOUTH = SOUTH + SOUTH;

const int NORTHWEST = NORTH + WEST;
const int NORTHEAST = NORTH + EAST;
const int SOUTHWEST = SOUTH + WEST;
const int SOUTHEAST = SOUTH + EAST;

const int SPACE = -8;
const int EMPTY_SQUARE = -1;

const int P = 0;
const int N = 1;
const int B = 2;
const int R = 3;
const int Q = 4;
const int K = 5;
const int p = 6;
const int n = 7;
const int b = 8;
const int r = 9;
const int q = 10;
const int k = 11;

const int initialBoard[SIZE] = {  // important: keep const keyword for initialboard!!!!
        -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
        -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
        -8, 9, 7, 8, 10, 11, 8, 7, 9, -8,
        -8, 6, 6, 6, 6, 6, 6, 6, 6, -8,
        -8, -1, -1, -1, -1, -1, -1, -1, -1, -8,
        -8, -1, -1, -1, -1, -1, -1, -1, -1, -8,
        -8, -1, -1, -1, -1, -1, -1, -1, -1, -8,
        -8, -1, -1, -1, -1, -1, -1, -1, -1, -8,
        -8, 0, 0, 0, 0, 0, 0, 0, 0, -8,
        -8, 3, 1, 2, 4, 5, 2, 1, 3, -8,
        -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
        -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,
};

const int DIRECTIONS[NUM_PIECES][9] = {
        {NORTH, NORTHNORTH, NORTHWEST, NORTHEAST, 0}, // pawn
        {NORTH + NORTHEAST, NORTH + NORTHWEST, EAST + EAST + NORTH,EAST + EAST + SOUTH,SOUTH + SOUTHEAST, SOUTH + SOUTHWEST,WEST + WEST + + SOUTH,WEST + WEST + NORTH, 0}, // knight
        {NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST, 0}, // bishop
        {NORTH, EAST, SOUTH, WEST, 0}, // rook
        {NORTH, EAST, SOUTH, WEST, NORTHEAST, SOUTHEAST,SOUTHWEST, NORTHWEST, 0}, // queen
        {NORTH, EAST, SOUTH, WEST, NORTHEAST, SOUTHEAST,SOUTHWEST, NORTHWEST, 0}, // king
        {SOUTH, SOUTHSOUTH, SOUTHWEST, SOUTHEAST, 0}, // pawn
        {NORTH + NORTHEAST, NORTH + NORTHWEST, EAST + EAST + NORTH,EAST + EAST + SOUTH,SOUTH +SOUTHEAST, SOUTH + SOUTHWEST,WEST + WEST + + SOUTH,WEST + WEST + NORTH, 0}, // knight
        {NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST, 0}, // bishop
        {NORTH, EAST, SOUTH, WEST, 0}, // rook
        {NORTH, EAST, SOUTH, WEST, NORTHEAST, SOUTHEAST,SOUTHWEST, NORTHWEST, 0}, // queen
        {NORTH, EAST, SOUTH, WEST, NORTHEAST, SOUTHEAST,SOUTHWEST, NORTHWEST, 0} // king
};

const char ALL_PIECES[NUM_PIECES] = "PNBRQKpnbrqk";

void copyBoard(int* dest, const int* src) {
    memcpy(dest, src, sizeof(int) * SIZE);
}
