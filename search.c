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

const int EVAL_ROUGHNESS = 15;
const int minDepth = 7;
const bool useKillerMove = true;
const bool useNullMove = true; // not used in endgames anyway
const bool useTT = true;
const bool useMtdf = true;

int numNodes = 0;

//int getNullMoveScore(Position *position, int depth) {
//    Move opponentMoves[MAX_BRANCHING_FACTOR];
//    Move bestChildMove;
//    Position duplicate;
//    duplicatePosition(position, &duplicate);
//    doMove(&duplicate, &nullMove);
//    return bound(&duplicate, depth, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
//}

//bool isKingInCheck(Position *position) {
//    return abs(getNullMoveScore(position, 1)) >= MATE_LOWER;
//}

int bound(Position* position, int depth, int gamma, bool canNullMove, Move moves[]);

void printInfo(int depth, int timeTaken, int score, int gamma) {
    printf("info depth %d timeTaken %d nodes %d nps %d score cp %d",
           depth, timeTaken, numNodes, numNodes / timeTaken, score);
    printf(score >= gamma ? "lowerbound" : "upperbound\n");
}


int mtdf(Position *position, int depth, clock_t startTime) {
    int score, gamma = 0;
    int lowerBound = -MATE_LOWER;
    int upperBound = MATE_LOWER;

    while (lowerBound < upperBound - EVAL_ROUGHNESS) {
        Move moves[MAX_BRANCHING_FACTOR];
        score = bound(position, depth, gamma, false, moves);

        if(score >= gamma) {
            lowerBound = score;
        } else {
            upperBound = score;
        }
        printInfo(depth, clock() - startTime, score, gamma);
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



int bound(Position* position, int depth, int gamma, bool canNullMove, Move moves[]) {
    numNodes++;

    depth = depth < 0 ? 0 : depth;

    if (position->score <= -MATE_LOWER) {
        return -MATE_UPPER;
    }

    int entryLowerBound, entryUpperBound;
    TpMoveEntry* ttEntry = lookupTpMove(position->hash);
    Move* bestTTMove;
    if(ttEntry == NULL) {
        entryLowerBound = -MATE_UPPER;
        entryUpperBound = MATE_UPPER;
        bestTTMove = NULL;
    } else {
        entryLowerBound = ttEntry->lowerBound;
        entryUpperBound = ttEntry->upperBound;
        if (ttEntry->depth >= depth) { // replace condition by == to get true minimax score with TT
            if(ttEntry->lowerBound >= gamma) {
                return ttEntry->lowerBound;
            }
            if(ttEntry->upperBound < gamma) {
                return ttEntry->upperBound;
            }
        }
        bestTTMove = &ttEntry->bestMove;
    }

    if(canNullMove && depth > 0 && isRepetition(position)) {
        return 0;
    }

    if(depth == 0) { // todo adapt
        return position->score;
    }

    int best, score;
    Move* move;
    int numMoves = genMoves(position, moves);
    sortMoves(moves, depth, bestTTMove, position->board, position->ep, numMoves);
    Position positionBackup;
    duplicatePosition(position, &positionBackup);

    best = -MATE_UPPER;
    for (int i = 0; i < numMoves; i++) {
        move = &moves[i];
        doMove(position, move);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move bestChildMove;
        score = -bound(position, depth - 1, 1-gamma, true,opponentMoves);
        undoMove(position, move, positionBackup);

        if (score > best) {
            best = score;
        }
        if(best >= gamma) {
            // todo save move for pv construction and killer heuristic
            break;
        }
    }
    if(best >= gamma) {
        saveScore(position->hash, depth, best, entryUpperBound, *bestMoveToSave, position->currentPly);
    }
    else {
        saveScore(position->hash, depth, entryLowerBound, best, *bestMoveToSave, position->currentPly);
    }
    return best;
}



Move searchBestMove(Position* position, int timeLeftMs, bool isWhite) {
    int timeTakenMs, score;
    Move bestMove;
    clock_t start = clock();
    numNodes = 0;
    for(int depth = 1; depth < 1000; depth++){
        score = mtdf(position, depth, start);
        bestMove = lookupTpMove(position->hash)->bestMove;
        timeTakenMs = (int)(clock() - start);
        int nps = timeTakenMs == 0.0 ? 0 : (int)(numNodes/(timeTakenMs/1000.0));
        char bestMoveUci[6];
        moveToUciMove(&bestMove, bestMoveUci);
        printf("info depth %d pv %s score cp %d\n", depth, bestMoveUci, score);
        printf("info time %d numNodes %d nps %d\n", (int)timeTakenMs, numNodes, nps);
        fflush(stdout);
    }
    return bestMove;
}