#include <stdio.h>
#include <time.h>
#include <math.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "search.h"
#include "tpMove.h"
#include "tpScore.h"
#include "moveScoreGenerator.h"

const int EVAL_ROUGHNESS = 15;
int numNodes;


int getNullMoveScore(Position *position, int newGamma, int depth) {
    Position duplicate;
    duplicatePosition(position, &duplicate);
    doMove(&duplicate, &nullMove);
    return bound(&duplicate, newGamma, depth,true);
}

int getMoveScore(Position *position, int gamma, int depth, Position *positionBackup, Move *move) {
    Move moveDuplicate;
    moveDuplicate = *move; // in case move comes from TpMove and gets overwritten in subtree
    doMove(position, move);
    int score = -bound(position, 1-gamma, depth-1, true);
    undoMove(position, &moveDuplicate, (*positionBackup));
    return score;
}

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

    int best, moveIndex, numActualMoves, score, step = 0;
    int valLower = QS - (depth * QS_A);
    Move actualMoves[MAX_BRANCHING_FACTOR];
    Move mv;
    Move* move = &mv;
    Position positionBackup;
    duplicatePosition(position, &positionBackup);

    best = -MATE_UPPER;
    while(true) {
        step = getNextMoveScoreLazy(step, position, gamma, depth, canNullMove, valLower,
                                    &positionBackup, actualMoves, &numActualMoves,
                                    &moveIndex, move, &score);
        if(step == STOP) {
            break;
        }
        best = score > best ? score : best;
        if(best >= gamma) {
            if(move->from != NULL_MOVE) {
                saveMove(position->hash, *move);
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
    int timeTakenMs, score;
    Move bestMove;
    char bestMoveUci[6];
    initTpScore();
    initTpMove();
    clock_t start = clock();
    numNodes = 0;
    for(int depth = 1; depth <= MAX_SEARCH_DEPTH && depth < 2; depth++){
        score = mtdf(position, depth, start, bestMoveUci);
        bestMove = *lookupTpMove(position->hash);
        timeTakenMs = (int)(clock() - start);
        int nps = timeTakenMs == 0.0 ? 0 : (int)(numNodes/(timeTakenMs/1000.0));
        printf("info depth %d pv %s score cp %d\n", depth, bestMoveUci, score);
        printf("info time %d numNodes %d nps %d\n", (int)timeTakenMs, numNodes, nps);
        fflush(stdout);
        if(timeTakenMs > 900 || abs(score) >= MATE_LOWER) {
            break;
        }
    }
    clearTpScore();
    clearTpMove();
    return bestMove;
}