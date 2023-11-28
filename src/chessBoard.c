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

int PIECE_INDEXES[PIECES_MAX_ASCII];

char const initialBoard[] = "          " // important: keep const keyword for initialboard!!!!
                            "          "
                            " rnbqkbnr "
                            " pppppppp "
                            " ........ "
                            " ........ "
                            " ........ "
                            " ........ "
                            " PPPPPPPP "
                            " RNBQKBNR "
                            "          "
                            "          ";

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

void initializePieceIndexArray() {
    for (int i = 0; i < NUM_PIECES; ++i) {
        PIECE_INDEXES[ALL_PIECES[i]] = i;
    }
}

void copyBoard(char* dest, const char* src) {
    memcpy(dest, src, sizeof(char) * SIZE);
}
