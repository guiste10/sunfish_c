#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "move.h"
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"
#include "uci.h"

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
        printf("%d\t", arr[i]); // similar to  *(arr + i)
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
    moveToUciMove(true, &move, uciMove);
    printf("Best move: %s\n", uciMove);
    fflush(stdout);  // Flush the output stream
}

void findBestMoveTimeStamped(char* boardToUse) {
    Position pos;
    Position* position = &pos;
    char board[SIZE];
    initPosition(position, board, (char*)boardToUse);
    printf("Current board\n");
    printCharArray(board, SIZE);
    clock_t start = clock();
    Move bestMove;
    searchBestMove(position, &bestMove, TIME_LEFT_DEBUG, true);
    printf("Best move search finished\nTime taken: %.2f ms\n", (double)clock()-start);
    Position newPosition;
    char newBoard[SIZE];
    doMove(position, &bestMove, &newPosition, newBoard);
    printMove(bestMove);
    printCharArray(newBoard, SIZE);
}

void findBestMoveFromUciPosition(char uciPosition[MAX_ARGS]) {
    bool isWhite = true;
    Position pos;
    Position* position = &pos;
    char* args[MAX_ARGS];
    int numArgs;

    fillArgs(uciPosition, args, &numArgs);
    char initialBoardCopy[SIZE];
    setupPosition(position, initialBoardCopy, &isWhite, args, numArgs);
    printf("Current board\n");
    printCharArray(initialBoardCopy, SIZE);
    Move bestMove;
    clock_t start = clock();
    searchBestMove(position, &bestMove, TIME_LEFT_DEBUG, isWhite);
    printf("Best move search finished\nTime taken: %.2f ms\n", (double)clock()-start);
    printMove(bestMove);
}