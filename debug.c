#include <stdio.h>
#include <time.h>
#include "move.h"
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"
#include "uci.h"
#include "tpMove.h"
#include "pieceSquareTables.h"

const int TIME_LEFT_DEBUG = 99999999;

void printIntArray(const int* arr, int size) {
    printf("Array:");
    for (int i = 0; i < size; i++) {
        if(i % 10 == 0){
            printf("\n");
        }
        printf("%d\t", arr[i]); // similar to  *(arr + from)
        fflush(stdout);  // Flush the output stream
    }
    printf("\n");
    fflush(stdout);  // Flush the output stream
}

void printCharArray(const char* arr, int size) {
    printf("Array:");
    for (int i = 0; i < size; i++) {
        if (i % 10 == 0) {
            printf("\n");
            fflush(stdout);  // Flush the output stream
        }
        printf("%c\t", arr[i]);
        fflush(stdout);  // Flush the output stream
    }
    printf("\n");
    fflush(stdout);  // Flush the output stream
}


void printMove(Move move) {
    char uciMove[6];
    moveToUciMove(&move, uciMove);
    printf("Best move: %s\n", uciMove);
    fflush(stdout);  // Flush the output stream
}

void findBestMoveFromUciPosition(char uciPosition[MAX_ARGS]) {
    bool isWhite = true;
    Position pos;
    Position* position = &pos;
    char* args[MAX_ARGS];
    int numArgs;

    initOpeningToMiddleGamePst();
    initializePieceIndexArray();
    fillArgs(uciPosition, args, &numArgs);
    char initialBoardCopy[SIZE];
    uint64_t history[MAX_PLY_CHESS_GAME];
    setupPositionWithMoveList(position, initialBoardCopy, &isWhite, args, numArgs, history);
    printf("Current board\n");
    printCharArray(position->board, SIZE);
    clock_t start = clock();
    initTpMove();
    Move bestMove = searchBestMove(position, TIME_LEFT_DEBUG);
    clearTpMove();
    printf("Best move search finished\nTime taken: %.2f ms\n", (double)clock()-start);
    printMove(bestMove);
}