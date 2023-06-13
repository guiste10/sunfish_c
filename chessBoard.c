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

const int P = 0;
const int N = 1;
const int B = 2;
const int R = 3;
const int Q = 4;
const int K = 5;

const char initialBoard[] = "          "
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
const char PROMOTIONS[] = "NBRQ";
const int NUM_PROMOTIONS = 4;

const int DIRECTIONS[NUM_PIECES][9] = {
        {NORTH, NORTH + NORTH, NORTH + WEST, NORTH + EAST, 0}, // pawn
        {NORTH + NORTH + EAST, NORTH + NORTH + WEST, // knight
         EAST + EAST + NORTH,EAST + EAST + SOUTH,
         SOUTH + SOUTH + EAST, SOUTH + SOUTH + WEST,
         WEST + WEST + + SOUTH,WEST + WEST + NORTH, 0},
        {NORTH + EAST, SOUTH + EAST, SOUTH + WEST, NORTH + WEST, 0}, // bishop
        {NORTH, EAST, SOUTH, WEST, 0}, // rook
        {NORTH, EAST, SOUTH, WEST, NORTH + EAST, // queen
         SOUTH + EAST,SOUTH + WEST, NORTH + WEST, 0},
        {NORTH, EAST, SOUTH, WEST, NORTH + EAST, // king
         SOUTH + EAST,SOUTH + WEST, NORTH + WEST, 0}
};

int getPieceIndex(char piece) {
    switch (piece) {
        case 'P':
            return 0;
        case 'N':
            return 1;
        case 'B':
            return 2;
        case 'R':
            return 3;
        case 'Q':
            return 4;
        case 'K':
            return 5;
        default:
            return -1;  // Return -1 for invalid characters
    }
}

void copyBoard(char* dest, const char* src) {
    memcpy(dest, src, sizeof(char) * SIZE);
}
