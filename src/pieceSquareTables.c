#include "constants.h"
#include "chessBoard.h"

const int pawnVal = 100;
const int knightVal = 280;
const int bishopVal = 320;
const int rookVal = 479;
const int queenVal = 929;
const int kingVal = 60000;
const int MATE_LOWER = kingVal - 10 * queenVal; // 50710
const int MATE_UPPER = kingVal + 10 * queenVal; // 69290

const int PIECE_VALUES[NUM_PIECES] = {
        pawnVal, knightVal, bishopVal, rookVal, queenVal, kingVal,
        pawnVal, knightVal, bishopVal, rookVal, queenVal, kingVal
};

int PST[NUM_PIECES][SIZE];

int SQUARE_VALUES[NUM_PIECES][SIZE] = {
        { // pawn
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0,   0,   0,   0,    0,   0,    0,   0,   0,
                0, 78,  83, 86,  73,  102, 82, 85, 90,  0,
                0, 28,   29, 21,  44, 40,  31,  44, 7,   0,
                0, 5, 10,  -2, 15, 14,  0,  15,  -13, 0,
                0, 10, 3,   15,  20,   20,   -10,   -10,   15, 0,
                0, 5, 9,   5,   5, 5, -20,  20,   20, 0,
                0, -1, -1,   -1,  -30, -20, 20, 3,   20, 0,
                0, 0,   0,   0,   0,   0,   0,   0,   0,   0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        { // knight
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, -66, -53, -75, -75, -10, -55, -58, -70, 0,
                0, -3, -6, 100, -36, 4, 62, -4, -14, 0,
                0, 10, 67, 1, 74, 73, 27, 62, -2, 0,
                0, 24, 24, 45, 37, 33, 41, 25, 17, 0,
                0, -1, 5, 31, 21, 22, 35, 2, 0, 0,
                0, -18, 10, 13, 22, 18, 15, 11, -14, 0,
                0, -23, -15, 2, 0, 2, 0, -23, -20, 0,
                0, -74, -23, -26, -24, -19, -35, -22, -69, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        { // bishop
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, -59, -78, -82, -76, -23, -107, -37, -50, 0,
                0, -11, 20, 35, -42, -39, 31, 2, -22, 0,
                0, -9, 39, -32, 41, 52, -10, 28, -14, 0,
                0, 25, 17, 20, 34, 26, 25, 15, 10, 0,
                0, 13, 10, 17, 23, 17, 16, 0, 7, 0,
                0, 14, 25, 24, 15, 8, 25, 20, 15, 0,
                0, 19, 20, 11, 6, 7, 6, 20, 16, 0,
                0, -7, 2, -15, -12, -14,    -15, -10, -10, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        { // rook
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 35,  29,  33,  30,  37,  33, 33,  33,  0,
                0, 30,  29, 30,  30,  30,  30, 34, 30,  0,
                0, 19,  35, 28,  33, 30,  27,  25, 19,  0,
                0, 0,   5,   16, 13, 18,  -4, -9,  -6,  0,
                0, -28, -35, -16, -21, -13, -29, -46, -30, 0,
                0, -42, -28, -42, -8, -8, -35, -26, -46, 0,
                0, -53, -38, -31, -2, -2, -43, -44, -53, 0,
                0, -20, -24, -18, 5,   5,  -18, -31, -32, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        { // queen
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 6,   1,   -8,  -104, 69,  24,   88,  26,  0,
                0, 14,  32, 60,  -10, 20,  76, 57, 24,  0,
                0, -2,  43, 32,  60, 72,  63,  43, 2,   0,
                0, 1,   -16, 22, 17, 25,  20, -13, -6,  0,
                0, -14, -15, -2,  -5,  -1,  -10, -20, -22, 0,
                0, -30, -6,  -13, -11, -16, -11, -16, -27, 0,
                0, -36, -18, 0,   -19, -15, -15, -21, -38, 0,
                0, -39, -30, -31, -13, -31, -36, -34, -42, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        },
        { // king
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 4,   54,  47,  -99,  -99, 60,   83,  -62, 0,
                0, -32, 10, 55,  56,  56,  55, 10, 3,   0,
                0, -62, 12, -57, 44, -67, 28,  37, -31, 0,
                0, -55, 50,  11, -4, -19, 13, 0,   -49, 0,
                0, -55, -43, -52, -28, -51, -47, -8,  -50, 0,
                0, -47, -42, -43, -79, -64, -32, -29, -32, 0,
                0, -4,  3,   -14, -50, -57, -18, 13,  4,   0,
                0, 17,  30,  -3,  -14, 6,   -1,  40,  18,  0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        }
};

const int SQUARES_VALUES_KING_ENDGAME[SIZE] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 10, 20, 20, 20, 20, 20, 20, 10, 0,
        0, 10, 20, 30, 30, 30, 30, 20, 10, 0,
        0, 10, 20, 30, 30, 30, 30, 20, 10, 0,
        0, 10, 20, 30, 30, 30, 30, 20, 10, 0,
        0, 10, 20, 30, 30, 30, 30, 20, 10, 0,
        0, 10, 15, 15, 15, 15, 15, 15, 10, 0,
        0, -5, 0, 5, 5, 5, 5, 0, -5, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const int SQUARES_VALUES_PAWN_ENDGAME[SIZE] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0,   0,   0,   0,    0,   0,    0,   0,   0,
        0, 78,  83, 86,  73,  102, 82, 85, 90,  0,
        0, 40,   40, 40,   40, 40,  40,  44, 40,   0,
        0, 20, 20,  20, 15, 20,  20, 20,  20, 0,
        0, 10, 10,   10,  9,   10,   10, 10,   10, 0,
        0, -10, -10,   -10,   -11, -10, -10,  -10,   -10, 0,
        0, -31, -30,   -30,  -30, -36, -30, -20,   -20, 0,
        0, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};


void initOpeningToMiddleGamePst(){
    int square, mirroredSquare;
    for(int row = 0; row < NUM_ROWS; row++){
        for(int col = 0; col < NUM_FILES; col++){
            for(int piece=0; piece < NUM_PIECES; piece++) {
                square = (10 * row) + col;
                mirroredSquare = 10 * (NUM_ROWS - row - 1) + col;
                if(piece >= NUM_WHITE_PIECES)  // mirror white's square values
                    SQUARE_VALUES[piece][square] = SQUARE_VALUES[piece - NUM_WHITE_PIECES][mirroredSquare];
                PST[piece][square] = SQUARE_VALUES[piece][square] + PIECE_VALUES[piece];
            }
        }
    }
}

void setPstToEndGame() {
    int square, mirroredSquare;
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_FILES; col++) {
            square = (10 * row) + col;
            mirroredSquare = 10 * (NUM_ROWS - row - 1) + col;
            SQUARE_VALUES[k][square] = SQUARE_VALUES[K][mirroredSquare];
            SQUARE_VALUES[p][square] = SQUARE_VALUES[P][mirroredSquare];
            PST[K][square] = SQUARES_VALUES_KING_ENDGAME[square] + PIECE_VALUES[K];
            PST[k][square] = SQUARES_VALUES_KING_ENDGAME[mirroredSquare] + PIECE_VALUES[k];
            PST[P][square] = SQUARES_VALUES_PAWN_ENDGAME[square] + PIECE_VALUES[P];
            PST[p][square] = SQUARES_VALUES_PAWN_ENDGAME[mirroredSquare] + PIECE_VALUES[p];
        }
    }
}

void setPstToEndGameIfEndGame(const char *board) {
    int queenCount = 0;
    for(int square = 0; square < SIZE ; square++) {
        char piece = board[square];
        if(piece == 'Q' || piece == 'q'){
            queenCount++;
            if(queenCount >= 2){
                return;
            }
        }
    }
    setPstToEndGame();
}