//
// Created by neiringu on 18-05-23.
//

#include <stdint.h>
#include "map.h"
#include "constants.h"
#include "chessBoard.h"

const int pawnVal = 100;
const int knightVal = 280;
const int bishopVal = 320;
const int rookVal = 479;
const int queenVal = 929;
const int kingVal = 60000;
const int MATE_LOWER = kingVal - 10 * queenVal;
const int MATE_UPPER = kingVal + 10 * queenVal;

const int NUM_PIECES = 6;

int pawn[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 78, 83, 86, 73, 102, 82, 85, 90, 0,
        0, 7, 29, 21, 44, 40, 31, 44, 7, 0,
        0, -17, 16, -2, 15, 14, 0, 15, -13, 0,
        0, -26, 3, 10, 9, 6, 1, 0, -23, 0,
        0, -22, 9, 5, -11, -10, -2, 3, -19, 0,
         0, -31, 8, -7, -37, -36, -14, 3, -31, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int knight[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,-66, -53, -75, -75, -10, -55, -58, -70,0,
        0,-3, -6, 100, -36, 4, 62, -4, -14,0,
        0,10, 67, 1, 74, 73, 27, 62, -2,0,
        0,24, 24, 45, 37, 33, 41, 25, 17,0,
        0,-1, 5, 31, 21, 22, 35, 2, 0,0,
        0,-18, 10, 13, 22, 18, 15, 11, -14,0,
        0,-23, -15, 2, 0, 2, 0, -23, -20,0,
        0,-74, -23, -26, -24, -19, -35, -22, -69,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int bishop[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,-59, -78, -82, -76, -23, -107, -37, -50,0,
        0,-11, 20, 35, -42, -39, 31, 2, -22,0,
        0,-9, 39, -32, 41, 52, -10, 28, -14,0,
        0,25, 17, 20, 34, 26, 25, 15, 10,0,
        0,13, 10, 17, 23, 17, 16, 0, 7,0,
        0,14, 25, 24, 15, 8, 25, 20, 15,0,
        0,19, 20, 11, 6, 7, 6, 20, 16,0,
        0,-7, 2, -15, -12, -14, -15, -10, -10,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int rook[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,35, 29, 33, 4, 37, 33, 56, 50,0,
        0,55, 29, 56, 67, 55, 62, 34, 60,0,
        0,19, 35, 28, 33, 45, 27, 25, 15,0,
        0,0, 5, 16, 13, 18, -4, -9, -6,0,
        0,-28, -35, -16, -21, -13, -29,-46, -30,0,
        0,-42, -28, -42, -25, -25, -35, -26, -46,0,
        0,-53, -38, -31, -26, -29, -43, -44, -53,0,
        0,-30, -24, -18, 5, -2, -18, -31, -32,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int queen[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,6, 1, -8, -104, 69, 24, 88, 26,0,
        0,14, 32, 60, -10, 20, 76, 57, 24,0,
        0,-2, 43, 32, 60, 72, 63, 43, 2,0,
        0,1, -16, 22, 17, 25, 20, -13, -6,0,
        0,-14, -15, -2, -5, -1, -10, -20, -22,0,
        0,-30, -6, -13, -11, -16, -11, -16, -27,0,
        0,-36, -18, 0, -19, -15, -15, -21, -38,0,
        0,-39, -30, -31, -13, -31, -36, -34, -42,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int king[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,4, 54, 47, -99, -99, 60, 83, -62,0,
        0,-32, 10, 55, 56, 56, 55, 10, 3,0,
        0,-62, 12, -57, 44, -67, 28, 37, -31,0,
        0,-55, 50, 11, -4, -19, 13, 0, -49,0,
        0,-55, -43, -52, -28, -51, -47, -8, -50,0,
        0,-47, -42, -43, -79, -64, -32, -29, -32,0,
        0,-4, 3, -14, -50, -57, -18, 13, 4,0,
        0,17, 30, -3, -14, 6, -1, 40, 18,0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

map* createPieceValues(){
    map* pieceValues = map_create();
    map_put(pieceValues, "P", (void*)(uintptr_t)pawnVal);
    map_put(pieceValues, "N", (void*)(uintptr_t)knight);
    map_put(pieceValues, "B", (void*)(uintptr_t)bishopVal);
    map_put(pieceValues, "R", (void*)(uintptr_t)rookVal);
    map_put(pieceValues, "Q", (void*)(uintptr_t)queenVal);
    map_put(pieceValues, "K", (void*)(uintptr_t)kingVal);
    return pieceValues;
}

map* createSquareValues(){
    map* squareValues = map_create();
    map_put(squareValues, "P", (void*)pawn);
    map_put(squareValues, "N", (void*)knight);
    map_put(squareValues, "B", (void*)bishop);
    map_put(squareValues, "R", (void*)rook);
    map_put(squareValues, "Q", (void*)queen);
    map_put(squareValues, "K", (void*)king);
    return squareValues;
}

map* createPst(){
    map* pieceValues = createPieceValues();
    map* squareValues = createSquareValues();
    for(int i=0; i < NUM_PIECES; i++){
        char pieceIdentifier[2] = {PIECES[i], '\0'};
        int valueForPiece = (int)(uintptr_t)map_get(pieceValues, pieceIdentifier);
        int* squareValuesForPiece = (int*)map_get(squareValues, pieceIdentifier);
        for(int j=0; j < SIZE; j++){
            *(squareValuesForPiece + j) = *(squareValuesForPiece + j) + valueForPiece;
        }
    }
    map_destroy(pieceValues);
    return squareValues;
}
