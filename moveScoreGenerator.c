#include <math.h>
#include <stdlib.h>
#include "moveScoreGenerator.h"
#include "position.h"
#include "search.h"
#include "move.h"
#include "tpMove.h"
#include "pieceSquareTables.h"

const int LAST = 5;
const int STOP = 6;

// returns the next step id
int getNextMoveScoreLazy(int step, Position* position, int gamma, int depth, bool canNull,
                         int valLower, Position* positionBackup, Move* actualMoves, int* numActualMoves,
                         int *moveIndex, Move* moveToYield, int* scoreToYield) {
    Move* move;
    switch (step) {
        case 0:
            if(depth > 2 && canNull && abs(position->score) < 500) {
                *moveToYield = nullMove;
                *scoreToYield = -getNullMoveScore(position, 1 - gamma, depth - 3);
                return 1;
            }
            break;
        case 1:
            if(depth == 0) {
                *moveToYield = nullMove;
                *scoreToYield = position->score;
                return 2;
            }
            break;
        case 2:
            move = lookupTpMove(position->hash);
            if(move == NULL && depth > 2) {
                bound(position, gamma, depth - 3, false);
                move = lookupTpMove(position->hash);
            }
            if(move != NULL && move->moveValue >= valLower) {
                *moveToYield = *move;
                *scoreToYield = getMoveScore(position, gamma, depth, positionBackup, move);
                return 3;
            }
            break;
        case 3:
            *numActualMoves = genActualMoves(position, actualMoves);
            assignMoveValues(position, actualMoves, *numActualMoves);
            qsort(actualMoves, *numActualMoves, sizeof(Move), compareMoves);
            *moveIndex = 0;
            break;
        case 4:
            if(*moveIndex == *numActualMoves) {
                return STOP;
            }
            move = &actualMoves[(*moveIndex)++];
            if(move->moveValue < valLower) {
                return STOP;
            }
            *moveToYield = *move;
            if(depth <= 1 && position->score + move->moveValue < gamma) {
                *scoreToYield = move->moveValue < MATE_LOWER ? position->score + move->moveValue : MATE_UPPER;
                return LAST;
            }
            *scoreToYield = getMoveScore(position, gamma, depth, positionBackup, move);
            return 4;
        case 5:
            return STOP;
    }
    return getNextMoveScoreLazy(step + 1, position, gamma, depth, canNull,valLower, positionBackup,
                                actualMoves, numActualMoves, moveIndex, moveToYield, scoreToYield);
}
