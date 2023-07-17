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
                          " r....rk. "
                          " ppp..pbp "
                          " ......p. "
                          " ...N.bQ. "
                          " ......p. "
                          " ........ "
                          " Pq..PPPP "
                          " R.K..B.R "
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


void printMove(Move move, char board[]) {
    char from[3];  // Local character array to store the "from" position
    char to[3];  // Local character array to store the "to" position

    render(move.i, from);
    render(move.j, to);

    printf("Move %c from i = %s to j = %s", board[move.i], from, to);
    move.prom == NO_PROMOTION ? printf("\n") : printf(", prom = %c\n", PIECES[move.prom]);
    fflush(stdout);  // Flush the output stream
}

void findBestMoveTimeStamped(char* boardToUse) {
    Position pos;
    Position* position = &pos;
    char board[SIZE];
    initPosition(position, board, (char*)boardToUse);
    clock_t start = clock();  // Start measuring time
    Move* bestMove = searchBestMove(position);
    clock_t end = clock();  // Stop measuring time
    double elapsedTime = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;  // Calculate elapsed time in ms
    printf("Best move search finished\nTime taken: %.2f ms\nNum nodes: %d => %.2f nodes/sec\n", elapsedTime, numNodes, numNodes/(elapsedTime/1000.0));
    Position newPosition;
    char newBoard[SIZE];
    doMove(position, bestMove, &newPosition, newBoard);
    printMove(*bestMove, position->board);
    printCharArray(newBoard, SIZE);
    free(bestMove);
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
    Move* bestMove = searchBestMove(position);
    printMove(*bestMove, position->board);
    free(bestMove);
}