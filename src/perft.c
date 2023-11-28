#include <time.h>
#include <stdio.h>
#include "perft.h"
#include "position.h"
#include "chessBoard.h"
#include "search.h"

void perft(Position* position, int depth) {
    ++numNodes;
    if(depth == 0) 
        return;

    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    Move moves[MAX_BRANCHING_FACTOR];
    Move move;
    int numActualMoves = genActualMoves(position, moves);
    for(int moveIndex = 0; moveIndex < numActualMoves; ++moveIndex) {
        move = moves[moveIndex];
        doMove(position, &move);
        perft(position, depth-1);
        undoMove(position, &move, positionBackup);
    }

}

void runPerft() {
    Position pos;
    Position* position = &pos;
    int initialBoardCopy[SIZE];
    uint64_t history[MAX_PLY_CHESS_GAME];
    initPosition(position, initialBoardCopy, (int *) initialBoard, history);
    numNodes = 0;
    clock_t start = clock();
    perft(position, 6);
    clock_t end = clock();
    double numTicks = (double)(end - start);
    double timeTakenSec = (double)(numTicks / CLOCKS_PER_SEC);
    printf("Perft finished: nodes: %d, nps: %d\n", numNodes, timeTakenSec == 0 ? 0 : (int)(numNodes/timeTakenSec));
    fflush(stdout);
}