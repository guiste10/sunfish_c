#include <time.h>
#include <stdio.h>
#include <search.h>
#include "perft.h"
#include "position.h"
#include "chessBoard.h"
#include "search.h"
#include "moveScoreGenerator.h"
#include "pieceSquareTables.h"

void perftBasic(Position* position, int depth) { // 9.6 million nps
    numNodes++;
    if(depth == 0) 
        return;

    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    Move moves[MAX_BRANCHING_FACTOR];
    Move move;
    int numActualMoves = genActualMoves(position, moves);
    for(int moveIndex = 0; moveIndex < numActualMoves; moveIndex++) {
        move = moves[moveIndex];
        doMove(position, &move);
        perftBasic(position, depth-1);
        undoMove(position, &move, positionBackup);
    }
}

void perftMoveOrdering(Position* position, int depth) { // 6.4 million nps
    numNodes++;
    if(depth == 0)
        return;

    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    Move moves[MAX_BRANCHING_FACTOR];
    Move move;
    int numActualMoves = genActualMoves(position, moves);
    assignMoveValuesAndType(position, moves, numActualMoves, depth);
    qsort(moves, numActualMoves, sizeof(Move), compareMoves);
    for(int moveIndex = 0; moveIndex < numActualMoves; moveIndex++) {
        move = moves[moveIndex];
        doMove(position, &move);
        perftMoveOrdering(position, depth-1);
        undoMove(position, &move, positionBackup);
    }
}

void perftMoveOrderingAndMateAndRepetitionAndPat(Position* position, int depth) { // 6.0 million nps
    numNodes++;

    if (position->score <= -MATE_LOWER) {
        return;
    }

    if(depth > 0 && isRepetition(position)) {
        return;
    }

    if(depth == 0)
        return;

    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    Move moves[MAX_BRANCHING_FACTOR];
    Move move;
    int numActualMoves = genActualMoves(position, moves);
    assignMoveValuesAndType(position, moves, numActualMoves, depth);
    qsort(moves, numActualMoves, sizeof(Move), compareMoves);
    for(int moveIndex = 0; moveIndex < numActualMoves; moveIndex++) {
        move = moves[moveIndex];
        doMove(position, &move);
        perftMoveOrderingAndMateAndRepetitionAndPat(position, depth-1);
        undoMove(position, &move, positionBackup);
    }

    if(depth > 2 && numActualMoves == 0) {
        getNullMoveScore(position, MATE_UPPER, 0);
    }
}

void runPerft() {
    Position pos;
    Position* position = &pos;
    char initialBoardCopy[SIZE];
    uint64_t history[MAX_PLY_CHESS_GAME];
    initPosition(position, initialBoardCopy, (char *) initialBoard, history);
    initializePieceIndexArray();
    numNodes = 0;
    clock_t start = clock();
    perftMoveOrderingAndMateAndRepetition(position, 6);
    int timeTakenSec = (int)((float)(clock() - start) / 1000.0);
    printf("Perft finished: nodes: %d, nps: %d\n", numNodes, timeTakenSec == 0 ? 0 : (int)(numNodes/timeTakenSec));
    fflush(stdout);
}