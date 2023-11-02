#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "search.h"
#include "transpositionTable.h"
#include "killerMovesTable.h"

const int minDepth = 7;
const bool useKillerMove = true;
const bool useNullMove = true; // not used in endgames anyway
const bool useTT = true;
const bool useMtdf = true;

int numNodes = 0;

int alphaBeta(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove, Move moves[], Move* bestMoveToSave);

bool onlyKingMoves(Move moves[], int numMoves, const char *board) {
    for (int i=0; i<numMoves; i++){
        char fromPiece = *(board + moves[i].from);
        if(fromPiece != 'K' && fromPiece != 'k'){
            return false;
        }
    }
    return true;
}

int getNullMoveScore(Position *position, int depth) {
    Move opponentMoves[MAX_BRANCHING_FACTOR];
    Move bestChildMove;
    Position duplicate;
    duplicatePosition(position, &duplicate);
    doMove(&duplicate, &nullMove);
    return alphaBeta(&duplicate, depth, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
}

bool isKingInCheck(Position *position) {
    return abs(getNullMoveScore(position, 1)) >= MATE_LOWER;
}

bool allKingMovesLeadToDeath(Position *position, int numMoves, Move kingMoves[]) {
    for (int i=0; i < numMoves; i++){
        Move* move = &kingMoves[i];
        Position positionBackup;
        duplicatePosition(position, &positionBackup);
        doMove(position, move);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move bestChildMove;
        int score = alphaBeta(position, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
        undoMove(position, move, positionBackup);
        if (abs(score) < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}

bool isPat(Position* position, int numMoves, Move moves[]) {
    if(onlyKingMoves(moves, numMoves, position->board) && !isKingInCheck(position)) {
        return allKingMovesLeadToDeath(position, numMoves, moves);
    }
    return false;
}

int getQuiescentDepth(int depth, Position *position, Move *move) {
    char fromPiece = position->board[move->to];
    char toPiece = move->pieceTo;
    if (depth == 1 && isCapture(move, position->board, position->ep) && PIECE_VALUES[PIECE_INDEXES_WHITE[fromPiece]] > PIECE_VALUES[PIECE_INDEXES_WHITE[toPiece]]) {
        return depth; // search one more ply because risky capture
    }
    return depth - 1;
}


int mtdf(Position* position, int firstGuess, int depth, Move* moves, Move* bestMove) {
    int g = firstGuess;
    int upperBound = INT_MAX;
    int lowerBound = INT_MIN;

    while (lowerBound < upperBound) {
        int beta;
        if (g == lowerBound)
            beta = g + 1;
        else
            beta = g;

        g = alphaBeta(position, depth, beta - 1, beta, true, false, moves, bestMove);
        if (g < beta)
            upperBound = g;
        else
            lowerBound = g;
    }

    return g;
}

int isThreefoldRepetition(const Position *position) {
    int repetitionCount = 0;
    for(int ply = position->plyIrreversible; ply < position->currentPly; ply++){
        if(position->history[ply] == position->hash){
            repetitionCount++;
        }
        if(repetitionCount == 2) {
            return true;
        }
    }
    return false;
}



int alphaBeta(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove,
              Move moves[], Move* bestMoveToSave) {
    numNodes++;

    depth = depth < 0 ? 0 : depth;

    if (position->score <= -MATE_LOWER) { // mated as white
        return -MATE_UPPER;
    }
    if (position->score >= MATE_LOWER) {
        return MATE_UPPER;
    }

    bool hasBestTTMove;
    Move bestMoveTT;
    int entryLowerBound, entryUpperBound;
    TranspositionEntry* ttEntry = lookupTT(position->hash);
    if(ttEntry == NULL) {
        entryLowerBound = -MATE_UPPER;
        entryUpperBound = MATE_UPPER;
    } else {
        entryLowerBound = ttEntry->lowerBound;
        entryUpperBound = ttEntry->upperBound;
        hasBestTTMove = true;
        bestMoveTT = ttEntry->bestMove;
        if (ttEntry->depth >= depth) { // replace condition by == to get true minimax score with TT
            if(ttEntry->lowerBound >= beta) {
                return ttEntry->lowerBound;
            }
            if(ttEntry->upperBound <= alpha) {
                return ttEntry->upperBound;
            }
            alpha = (alpha > ttEntry->lowerBound ? alpha : ttEntry->lowerBound);
            beta = (beta < ttEntry->upperBound ? beta : ttEntry->upperBound);
        }
    }

    if(isThreefoldRepetition(position)) {
        return 0;
    }

    int g, score;
    Move* move;
    if (depth <= 0) {
        g = position->score;
    } else {
        int numMoves = genMoves(position, moves);
        if (doPatCheck && isPat(position, numMoves, moves)) { // todo change as in sunfish
            return 0;
        }
        sortMoves(moves, depth, hasBestTTMove, &bestMoveTT, position->board, position->ep, numMoves);
        Position positionBackup;
        duplicatePosition(position, &positionBackup);
        if (position->isWhite) {
            g = -MATE_UPPER;
            int al = alpha;
            for (int i = 0; g < beta && i < numMoves; i++) {
                move = &moves[i];
                doMove(position, move);
                Move opponentMoves[MAX_BRANCHING_FACTOR];
                Move bestChildMove;
                score = alphaBeta(position, getQuiescentDepth(depth, position, move), al, beta, true, true,
                                  opponentMoves, &bestChildMove);
                undoMove(position, move, positionBackup);

                if (score >= g) {
                    g = score;
                    *bestMoveToSave = *move;
                }
                if(g > al) {
                    al = g;
                }
            }
        } else {
            g = MATE_UPPER;
            int bet = beta;
            for (int i = 0; beta > alpha && i < numMoves; i++) {
                move = &moves[i];
                doMove(position, move);
                Move opponentMoves[MAX_BRANCHING_FACTOR];
                Move bestChildMove;
                score = alphaBeta(position, getQuiescentDepth(depth, position, move), alpha, bet, true, true,
                                  opponentMoves, &bestChildMove);
                undoMove(position, move, positionBackup);

                if (score <= g) {
                    g = score;
                    *bestMoveToSave = *move;
                }
                if(g < bet) {
                    bet = g;
                }
            }
        }
    }
    if(g <= alpha) {
        entryUpperBound = g;
    }
    if(g >= beta) {
        entryLowerBound = g;
    }
    saveScore(position->hash, depth, entryLowerBound, entryUpperBound, *bestMoveToSave, position->currentPly);
    return g;
}



void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite) {
    int timeTakenMs;
    int score = 0;
    int mtdfFirstGuess[2] = {0, 0};
    clock_t start = clock();
    numNodes = 0;
    bool isMate = false;
    bool canFurtherIncreaseDepth = true;
    initKillerMovesTable();
    const int maxDepth = timeLeftMs > 40000 ? 10 : timeLeftMs > 15000 ? 6 : 4;
    for(int depth = 1; depth <= 7; depth++){
    //for(int depth = 1; !isMate  && (depth <= minDepth || canFurtherIncreaseDepth) && depth <= maxDepth; depth++){
        Move moves[MAX_BRANCHING_FACTOR];
        score = useMtdf
                ? mtdf(position, mtdfFirstGuess[depth % 2], depth, moves, bestMove)
                : alphaBeta(position, depth, -INT_MAX, INT_MAX, false, false, moves, bestMove);
        mtdfFirstGuess[depth % 2] = score;
        timeTakenMs = (int)(clock() - start);
        int nps = timeTakenMs == 0.0 ? 0 : (int)(numNodes/(timeTakenMs/1000.0));

        char bestMoveUci[6];
        moveToUciMove(bestMove, bestMoveUci);
        if(depth > 1) {
            printf("info depth %d pv %s score cp %d\n", depth, bestMoveUci, score);
            printf("info time %d numNodes %d nps %d\n", (int)timeTakenMs, numNodes, nps);
            fflush(stdout);
        }
        isMate = abs(score) >= MATE_LOWER;
        canFurtherIncreaseDepth = timeTakenMs < 700.0;
    }
}