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


int numNodes = 0;
char* currentBoard;
bool isEndGame = false;

int alphaBeta(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove,
              Move moves[MAX_BRANCHING_FACTOR], Move* bestMoveToSave);

bool onlyKingMoves(Move moves[MAX_BRANCHING_FACTOR], int numMoves, const char *board) {
    for (int i=0; i<numMoves; i++){
        char fromPiece = *(board + moves[i].from);
        if(fromPiece != 'K' && fromPiece != 'k'){
            return false;
        }
    }
    return true;
}

bool isKingInCheck(Position *position) {
    Move opponentMoves[MAX_BRANCHING_FACTOR];
    Move bestChildMove;
    Move nullMove = {0, 666, 0};
    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    doMove(position, &nullMove);
    int score = alphaBeta(position, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
    undoMove(position, &nullMove, positionBackup);
    return score >= MATE_LOWER;
}

bool allKingMovesLeadToDeath(Position *position, int numMoves, Move kingMoves[MAX_BRANCHING_FACTOR]) {
    for (int i=0; i < numMoves; i++){
        Move* move = &kingMoves[i];
        Position positionBackup;
        duplicatePosition(position, &positionBackup);
        doMove(position, move);
        Move opponentMoves[MAX_BRANCHING_FACTOR];
        Move bestChildMove;
        int score = alphaBeta(position, 1, -INT_MAX, INT_MAX, false, false, opponentMoves, &bestChildMove);
        undoMove(position, move, positionBackup);
        if (score < MATE_LOWER) { // one safe move has been found
            return false;
        }
    }
    return true;
}

bool isPat(Position* position, int numMoves, Move moves[MAX_BRANCHING_FACTOR]) {
    if(onlyKingMoves(moves, numMoves, position->board) && !isKingInCheck(position)) {
        return allKingMovesLeadToDeath(position, numMoves, moves);
    }
    return false;
}

int compareMoves(const void* x, const void* y) {
    Move* moveA = (Move*)x;
    Move* moveB = (Move*)y;
    char toPieceA = currentBoard[moveA->to];
    char toPieceB = currentBoard[moveB->to];
    if(toPieceA != '.' && toPieceB != '.'){
        char fromPieceA = currentBoard[moveA->from];
        char fromPieceB = currentBoard[moveB->from];
        return (pieceValues[PIECE_INDEXES_WHITE[toPieceB]] - pieceValues[PIECE_INDEXES_WHITE[fromPieceB]]) -
               (pieceValues[PIECE_INDEXES_WHITE[toPieceA]] - pieceValues[PIECE_INDEXES_WHITE[fromPieceA]]); // prioritize winning captures (e.g. pawn takes queen)
    }
    else if(toPieceA != '.'){
        return -1; // negative number -> move A must be ordered before move B since it is a pieceTo
    }
    else if(toPieceB != '.'){
        return 1;
    }
    char fromPieceA = currentBoard[moveA->from];
    char fromPieceB = currentBoard[moveB->from];
    int pieceIndexA = PIECE_INDEXES[fromPieceA];
    int pieceIndexB = PIECE_INDEXES[fromPieceB];

    int scoreA = PST[pieceIndexA][moveA->to] - PST[pieceIndexB][moveA->from];
    int scoreB = PST[pieceIndexB][moveB->to] - PST[pieceIndexB][moveB->from];

    return isupper(fromPieceA) ? scoreB - scoreA : scoreA - scoreB;
}

int getQuiescentDepth(int depth, Position *position, Move *move) {
    char fromPiece = position->board[move->from];
    char toPiece = position->board[move->to];
//    if (depth == 1 && toPiece != '.' && pieceValues[PIECE_INDEXES_WHITE[fromPiece]] > pieceValues[PIECE_INDEXES_WHITE[toPiece]]) {
//        return depth; // search one more ply
//    }
    return depth - 1;
}

//    if(canNullMove && depth > 3 && !isEndGame){ // null move
//        Position target;
//        char targetBoard[SIZE];
//        Position* duplicatePos = duplicatePosition(position, &target, targetBoard);
//        rotate(duplicatePos, true);
//        Move opponentMoves[MAX_BRANCHING_FACTOR];
//        Move bestChildMove;
//        int score = -alphaBeta(duplicatePos, depth - 3, -beta, -alpha, false, false, opponentMoves, &bestChildMove);
//        if(score >= beta){
//            return beta;
//        }
//    }

int alphaBeta(Position* position, int depth, int alpha, int beta, bool doPatCheck, bool canNullMove,
              Move moves[MAX_BRANCHING_FACTOR], Move* bestMoveToSave) {    numNodes++;
    if (position->score <= -MATE_LOWER) { // mated as white
        return -MATE_UPPER;
    }
    if (position->score >= MATE_LOWER) {
        return MATE_UPPER;
    }
    if (depth == 0) {
        return position->score;
    }

    int numMoves = genMoves(position, moves);
    if(doPatCheck && isPat(position, numMoves, moves) == true) {
        return 0;
    }

    currentBoard = position->board;
    qsort(moves, numMoves, sizeof(Move), compareMoves);

    Position positionBackup;
    duplicatePosition(position, &positionBackup);
    if(position->isWhite){
        int max = -INT_MAX;
        for (int i = 0; i < numMoves; i++) {
            Move* move = &moves[i];
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

            if (score > max) {
                max = score;
                *bestMoveToSave = *move;
            }
            alpha = (alpha > score) ? alpha : score;
            if (alpha >= beta) {
                break;
            }
        }
        return max;
    } else {
        int min = INT_MAX;
        for (int i = 0; i < numMoves; i++) {
            Move* move = &moves[i];
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

            if (score < min) {
                min = score;
                *bestMoveToSave = *move;
            }
            beta = (beta < score) ? beta : score;
            if (alpha >= beta) {
                break;
            }
        }
        return min;
    }

}

void setIsEndGame(const char* board) {
    int numFriendlyPieces = 0;
    for(int square = 0; square < SIZE ; square++) {
        char piece = board[square];
        if(piece != '.' && isupper(piece) && piece != 'P'){
            numFriendlyPieces++;
        }
    }
    isEndGame = numFriendlyPieces <= 2;
}

void searchBestMove(Position* position, Move* bestMove, int timeLeftMs, bool isWhite) {
    setIsEndGame(position->board);
    double timeTakenMs;
    int score;
    clock_t start = clock();
    bool isMate = false;
    bool canFurtherIncreaseDepth = true;
    const int minDepth = 6;
    const int maxDepth = 6;
    //for(int depth = 6; depth == 6; depth++){
    for(int depth = 1; !isMate && (depth <= minDepth || canFurtherIncreaseDepth); depth++){
        Move moves[MAX_BRANCHING_FACTOR];
        numNodes = 0;
        score = alphaBeta(position, depth, -INT_MAX, INT_MAX, false, false, moves, bestMove);
        timeTakenMs = clock() - start;
        double nps = timeTakenMs == 0.0 ? 0 : numNodes/(timeTakenMs/1000.0);
        printf("info depth %d time %.2f nps %.2f\n", depth, timeTakenMs, nps);
        char bestMoveUci[6];
        moveToUciMove(bestMove, bestMoveUci);
        printf("info pv %s score cp %d\n", bestMoveUci, score);
        fflush(stdout);
        isMate = abs(score) >= MATE_LOWER;
        canFurtherIncreaseDepth = timeTakenMs < 700.0 && timeLeftMs > 10000;
    }
}