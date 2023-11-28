#include <stdio.h>
#include <time.h>
#include <search.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "search.h"
#include "tpMove.h"
#include "tpScore.h"
#include "moveScoreGenerator.h"
#include "killerMovesTable.h"

const int EVAL_ROUGHNESS = 15;
int numNodes;

void printInfo(int depth, int timeTakenMs, int score, int gamma, Position* position, char bestMoveUci[6]) {
    printf("info depth %d time %d nodes %d nps %d score cp %d ",
           depth, timeTakenMs, numNodes, timeTakenMs == 0.0 ? 0 : (int)(numNodes/(timeTakenMs/1000.0)), score);
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
        printInfo(depth, (int)(((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000.0), score, gamma, position, bestMoveUci);
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

    if(canNullMove && depth > 0 && isRepetition(position)) {
        return 0;
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

    int best, moveIndex, numActualMoves, score, step = 0;
    int valLower = QS - (depth * QS_A);
    Move actualMoves[MAX_BRANCHING_FACTOR];
    Move move;
    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    best = -MATE_UPPER;
    while(true) {
        step = getNextMoveScoreLazy(step, position, gamma, depth, canNullMove, valLower,
                                    &positionBackup, actualMoves, &numActualMoves,
                                    &moveIndex, &move, &score);
        if(step == STOP) {
            break;
        }
        best = score > best ? score : best;
        if(best >= gamma) {
            if(move.from != NULL_MOVE) {
                saveMove(position->hash, move);
                saveAsKillerMove(&move, depth, position->ep, position->board);
            }
            break;
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



Move searchBestMove(Position* position, int timeLeftMs) {
    int score;
    double secTakenForDepth;
    char bestMoveUci[6];
    clock_t start = clock();
    numNodes = 0;
    bool stop = false;
    for(int depth = 1; !stop && depth <= MAX_SEARCH_DEPTH; depth++){
        score = mtdf(position, depth, start, bestMoveUci);
        secTakenForDepth = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        int nps = secTakenForDepth == 0.0 ? 0 : (int)(numNodes / secTakenForDepth);
        printf("info depth %d pv %s score cp %d\n", depth, bestMoveUci, score);
        printf("info time %d numNodes %d nps %d\n", (int)(secTakenForDepth*1000), numNodes, nps);
        fflush(stdout);
        if(depth >= MIN_SEARCH_DEPTH && secTakenForDepth > 0.9 || (depth >= 6 && timeLeftMs < 15000)) {
            stop = true;
        }
    }
    return *lookupTpMove(position->hash);
}