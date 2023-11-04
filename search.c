#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "search.h"
#include "tpMove.h"
#include "tpScore.h"
#include "moveScoreGenerator.h"

const int EVAL_ROUGHNESS = 15;
const int minDepth = 7;
const bool useKillerMove = true;
const bool useNullMove = true; // not used in endgames anyway
const bool useTT = true;
const bool useMtdf = true;

int numNodes = 0;


int getNullMoveScore(Position *position, int newGamma, int depth) {
    Position duplicate;
    duplicatePosition(position, &duplicate);
    doMove(&duplicate, &nullMove);
    return bound(&duplicate, newGamma, depth,true);
}

void printInfo(int depth, int timeTaken, int score, int gamma, Position* position, char bestMoveUci[6]) {
    printf("info depth %d timeTaken %d nodes %d nps %d score cp %d ",
           depth, timeTaken, numNodes, timeTaken == 0 ? 0 : numNodes / timeTaken, score);
    printf(score >= gamma ? "lowerbound " : "upperbound");
    if(score >= gamma) {
        moveToUciMove(lookupTpMove(position->hash), bestMoveUci);
        printf("pv %s", bestMoveUci);
    }
    printf("\n");
}


int mtdf(Position *position, int depth, clock_t startTime, char bestMoveUci[6]) {
    int score, gamma = 0;
    int lowerBound = -MATE_LOWER;
    int upperBound = MATE_LOWER;

    while (lowerBound < upperBound - EVAL_ROUGHNESS) {
        score = bound(position, gamma, depth, false);

        if(score >= gamma) {
            lowerBound = score;
        } else {
            upperBound = score;
        }
        printInfo(depth, clock() - startTime, score, gamma, position, bestMoveUci);
        gamma = (lowerBound + upperBound + 1) / 2;
    }
    return gamma;
}

int isRepetition(const Position *position) {
    for(int ply = position->plyIrreversible; ply < position->currentPly; ply++){
        if(position->history[ply] == position->hash){
            return true;
        }
    }
    return false;
}

int bound(Position *position, int gamma, int depth, bool canNullMove) {
    numNodes++;

    depth = depth > 0 ? depth : 0;

    if (position->score <= -MATE_LOWER) {
        return -MATE_UPPER;
    }

    int entryLowerBound, entryUpperBound;
    TpScoreEntry* ttEntry = lookupTpScore(position->hash, depth, canNullMove);
    if(ttEntry == NULL) {
        entryLowerBound = -MATE_UPPER;
        entryUpperBound = MATE_UPPER;
    } else {
        entryLowerBound = ttEntry->lowerBound;
        entryUpperBound = ttEntry->upperBound;
        if(ttEntry->lowerBound >= gamma) {
            return ttEntry->lowerBound;
        }
        if(ttEntry->upperBound < gamma) {
            return ttEntry->upperBound;
        }
    }

    if(canNullMove && depth > 0 && isRepetition(position)) {
        return 0;
    }

    int best, moveIndex, numActualMoves, score;
    int valLower = QS - (depth * QS_A);
    Move actualMoves[MAX_BRANCHING_FACTOR];
    Move mv;
    Move* move = &mv;
    Position positionBackup;
    duplicatePosition(position, &positionBackup);

    best = -MATE_UPPER;
    for (int step = 0; step < STOP; ) {
        step = getMoveScoresLazy(step, position, gamma, depth, canNullMove, valLower,
                                 &positionBackup, actualMoves, &numActualMoves,
                                 &moveIndex, move, &score);
        best = score > best ? score : best;
        if(best >= gamma) {
            if(move->moveType != nullType) {
                saveMove(position->hash, *move);
            }
            break;
        }
        if(step == LAST) {
            step = STOP;
        }
    }

    if(depth > 2 && best == -MATE_UPPER) {
        bool inCheck = getNullMoveScore(position, MATE_UPPER, 0) == MATE_UPPER;
        best = inCheck ? -MATE_LOWER : 0;
    }

    if(best >= gamma) {
        saveScore(position->hash, depth, canNullMove, best, entryUpperBound);
    } else {
        saveScore(position->hash, depth, canNullMove, entryLowerBound, best);
    }
    return best;
}



Move searchBestMove(Position* position, int timeLeftMs, bool isWhite) {
    int timeTakenMs, score;
    Move bestMove;
    char bestMoveUci[6];
    clock_t start = clock();
    numNodes = 0;
    for(int depth = 1; depth <= 1; depth++){
        score = mtdf(position, depth, start, bestMoveUci);
        bestMove = *lookupTpMove(position->hash);
        timeTakenMs = (int)(clock() - start);
        int nps = timeTakenMs == 0.0 ? 0 : (int)(numNodes/(timeTakenMs/1000.0));
        printf("info depth %d pv %s score cp %d\n", depth, bestMoveUci, score);
        printf("info time %d numNodes %d nps %d\n", (int)timeTakenMs, numNodes, nps);
        fflush(stdout);
    }
    return bestMove;
}