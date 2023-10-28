#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "position.h"
#include "constants.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include "chessBoard.h"
#include "search.h"
#include "transpositionTable.h"
#include "killerMovesTable.h"


int numNodes = 0;
bool isEndGame = false;

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
    if (depth == 1 && toPiece != '.' && pieceValues[PIECE_INDEXES_WHITE[fromPiece]] > pieceValues[PIECE_INDEXES_WHITE[toPiece]]) {
        return depth; // search one more ply because risky capture
    }
    return depth - 1;
}


int mtdf(Position* position, int firstGuess, int depth, Move* bestMove) {
    int g = firstGuess;
    int upperBound = INT_MAX;
    int lowerBound = INT_MIN;

    while (lowerBound < upperBound) {
        int beta;
        if (g == lowerBound)
            beta = g + 1;
        else
            beta = g;

        Move moves[MAX_BRANCHING_FACTOR];
        g = alphaBeta(position, depth, beta - 1, beta, true, true, moves, bestMove);
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

    if(isThreefoldRepetition(position)) {
        return 0;
    }

    TranspositionEntry* ttEntry = lookupTT(position->hash);
    bool hasBestTTMove = false;
    Move bestMoveTT;
    if(ttEntry != NULL) {
        if (ttEntry->depth >= depth) {
            if (ttEntry->type == EXACT) { // todo search killer moves after winning/equal captures
                return ttEntry->score;
            } else if (ttEntry->type == LOWER) {
                alpha = (alpha > ttEntry->score ? alpha : ttEntry->score);
            } else if (ttEntry->type == UPPER) {
                beta = (beta < ttEntry->score ? beta : ttEntry->score);
            }
            if (alpha >= beta) {
                return ttEntry->score;
            }
        }
        if(ttEntry->type == EXACT) {
            hasBestTTMove = true;
            bestMoveTT = ttEntry->bestMove;
        }
    }

    int alphaOrig = alpha;
    int betaOrig = beta;

    if (position->score <= -MATE_LOWER) { // mated as white
        return -MATE_UPPER;
    }
    if (position->score >= MATE_LOWER) {
        return MATE_UPPER;
    }
    if (depth <= 0) {
        return position->score;
    }

    int numMoves = genMoves(position, moves);
    if (doPatCheck && isPat(position, numMoves, moves)) {
        return 0;
    }

    int bestScore;
    if(canNullMove && depth > 2 && !isEndGame){ // null move
        bestScore = getNullMoveScore(position, depth - 3);
        if(position->isWhite) {
            alpha = (alpha > bestScore) ? alpha : bestScore;
        } else {
            beta = (beta < bestScore) ? beta : bestScore;
        }
    } else {
        bestScore = position->isWhite ? -INT_MAX : INT_MAX;
    }

    Position positionBackup;
    if(alpha <= beta) { // only sort moves if there is no alpha-beta pruning caused by null move heuristic
        flagMovesWithType(moves, numMoves, depth, hasBestTTMove, &bestMoveTT);
        currentBoard = position->board;
        sortMoves(moves, numMoves);
        duplicatePosition(position, &positionBackup);
    }

    Move* move;
    if (position->isWhite) {
        for (int i = 0; beta > alpha && i < numMoves; i++) {
            move = &moves[i];
            doMove(position, move);
            Move opponentMoves[MAX_BRANCHING_FACTOR];
            Move bestChildMove;
            int score = alphaBeta(position, getQuiescentDepth(depth, position, move), alpha, beta, true, true,
                                  opponentMoves, &bestChildMove);
            undoMove(position, move, positionBackup);
            if (score >= MATE_LOWER) {
                score--; // winning mate found, add one point penalty per depth
            } else if (score <= -MATE_LOWER) {
                score++; // losing mate found, add one point penalty per depth
            }

            if (score > bestScore) {
                bestScore = score;
                *bestMoveToSave = *move;
            }
            alpha = (alpha > bestScore) ? alpha : bestScore;
        }
    } else {
        for (int i = 0; beta > alpha && i < numMoves; i++) {
            move = &moves[i];
            doMove(position, move);
            Move opponentMoves[MAX_BRANCHING_FACTOR];
            Move bestChildMove;
            int score = alphaBeta(position, getQuiescentDepth(depth, position, move), alpha, beta, true, true,
                                  opponentMoves, &bestChildMove);
            undoMove(position, move, positionBackup);
            if (score >= MATE_LOWER) {
                score--; // winning mate found, add one point penalty per depth
            } else if (score <= -MATE_LOWER) {
                score++; // losing mate found, add one point penalty per depth
            }

            if (score < bestScore) {
                bestScore = score;
                *bestMoveToSave = *move;
            }
            beta = (beta < bestScore) ? beta : bestScore;
        }
    }
    saveScore(position->hash, depth, bestScore, (bestScore <= alphaOrig) ? UPPER : (bestScore >= betaOrig) ? LOWER : EXACT, *bestMoveToSave);
    return bestScore;
}

void setIsEndGame(const char *board) {
    if(!isEndGame) {
        int numFriendlyPieces = 0;
        int queenCount = 0;
        for(int square = 0; square < SIZE ; square++) {
            char piece = board[square];
            if(piece == 'Q' || piece == 'q'){
                queenCount++;
                if(queenCount >= 2){
                    return;
                }
            }
        }
        isEndGame = true;
        initEndGamePst();
    }
}

void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite) {
    setIsEndGame(position->board);
    double timeTakenMs;
    int score = 0;
    clock_t start = clock();
    bool isMate = false;
    bool canFurtherIncreaseDepth = true;
    initTranspositionTable();
    //initKillerMovesTable();
    const int minDepth = 6;
    const int maxDepth = 8;
    //for(int depth = 1; depth <= 7; depth++){
    for(int depth = 1; !isMate  && (depth <= minDepth || canFurtherIncreaseDepth) && depth <= maxDepth; depth++){
        Move moves[MAX_BRANCHING_FACTOR];
        numNodes = 0;
        //score = alphaBeta(position, depth, -INT_MAX, INT_MAX, false, false, moves, bestMove);
        score = mtdf(position, score, depth, bestMove);
        timeTakenMs = clock() - start;
        double nps = timeTakenMs == 0.0 ? 0 : numNodes/(timeTakenMs/1000.0);
        printf("info depth %d time %d nps %d\n", depth, (int)timeTakenMs, (int)nps);
        printf("numNodes %d\n", numNodes);
        char bestMoveUci[6];
        moveToUciMove(bestMove, bestMoveUci);
        printf("info pv %s score cp %d\n", bestMoveUci, score);
        fflush(stdout);
        isMate = abs(score) >= MATE_LOWER;
        canFurtherIncreaseDepth = timeTakenMs < 700.0 && timeLeftMs > 10000;
    }
    clearTranspositionTable();
    //clearKillerMovesTable();
}