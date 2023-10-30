#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "move.h"
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"
#include "uci.h"
#include "zobrist.h"
#include "transpositionTable.h"
#include "pieceSquareTables.h"

const char debugBoard[] = "          "
                          "          "
                          " ........ "
                          " ........ "
                          " ........ "
                          " ........ "
                          " ..k..... "
                          " ..q..... "
                          " K....... "
                          " ........ "
                          "          "
                        "          ";

const char debugBoard2[] = "          "
                           "          "
                           " k....... "
                           " ........ "
                           " ........ "
                           " ........ "
                           " ........ "
                           " ........ "
                           " ........ "
                           " ....K..R "
                           "          "
                           "          ";

const char debugBoard3[] = "          "
                          "          "
                          " k....... "
                          " ........ "
                          " ........ "
                          " ........ "
                          " ........ "
                          " ........ "
                          " ........ "
                          " K....... "
                          "          "
                          "          ";

const char randomBoard[] = "          "
                          "          "
                          " r.k..b.r "
                          " pp..pppp "
                          " ........ "
                          " ...Q.b.. "
                          " ...n.Bq. "
                          " ......P. "
                          " PPP..PBP "
                          " R...K..R "
                          "          "
                          "          ";

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

void findBestMoveTimeStamped(char* boardToUse) {
    Position pos;
    Position* position = &pos;
    char board[SIZE];
    uint64_t history[MAX_PLY_CHESS_GAME];
    initOpeningToMiddleGamePst();
    initializePieceIndexArray();
    initPosition(position, board, boardToUse, history);
    if(isEndGame(position->board)){
        setPstToEndGameMode();
    }
    printf("Current board\n");
    printCharArray(board, SIZE);
    clock_t start = clock();
    Move bestMove;
    //initTranspositionTable();
    searchBestMove(position, &bestMove, TIME_LEFT_DEBUG, true);
    //clearTranspositionTable();
    printf("Best move search finished\nTime taken: %.2f ms\n", (double)clock()-start);
    doMove(position, &bestMove);
    printMove(bestMove);
    //printCharArray(newBoard, SIZE);
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
    Move bestMove;
    clock_t start = clock();
    //initTranspositionTable();
    searchBestMove(position, &bestMove, TIME_LEFT_DEBUG, isWhite);
    //clearTranspositionTable();
    printf("Best move search finished\nTime taken: %.2f ms\n", (double)clock()-start);
    printMove(bestMove);
//    doMove(position, &bestMove);
//    printCharArray(position->board, SIZE);
}