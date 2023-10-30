#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"
#include "pieceSquareTables.h"

const int MAX_ARGS = 1000;
const char BOT_NAME[] = "DiggyDiggyHole";

void fillArgs(char* line, char* args[MAX_ARGS], int* numArgs){
    *numArgs = 0;
    char *token = strtok(line, " \n");
    while (token != NULL && *numArgs < MAX_ARGS) {
        args[(*numArgs)++] = token;
        token = strtok(NULL, " \n");
    }
}

void setupPositionWithMoveList(Position* position, char* initialBoardCopy, bool* isWhite, char *uciMoves[1000], int numArgs, uint64_t* history){
    bool isEndGameReached = false;
    initPosition(position, initialBoardCopy, (char *) initialBoard, history);
    for (int ply = 0; ply < numArgs - 3; ply++) {
        if(!isEndGameReached && isEndGame(position->board)){
            isEndGameReached = true;
            setPstToEndGameMode();
        }
        char *uciMove = uciMoves[3 + ply];
        Move move;
        uciMoveToMove(uciMove, &move, *isWhite);
        *isWhite = !*isWhite;
        doMove(position, &move);
    }
}

void playOpening(const Position *position, int currentPly) {
    int e5 = 55;
    if(currentPly == 0) {
        printf("bestmove g1f3\n");
    } else if(currentPly == 1) {
        printf("bestmove g7g6\n");
    } else if(currentPly == 2) {
        if(position->board[e5] == '.') {
            printf("bestmove g2g3\n");
        } else {
            printf("bestmove f3e5\n");
        }
    } else {
        if(position->board[e5] == '.') {
            printf("bestmove f8g7\n");
        } else {
            printf("bestmove d7d6\n");
        }
    }
}

void playUci(){
    char line[10000];
    char* args[MAX_ARGS];
    int numArgs;
    bool isWhite;
    Position pos;
    Position* position = &pos;
    char initialBoardCopy[SIZE];
    uint64_t history[MAX_PLY_CHESS_GAME];
    initializePieceIndexArray();
    initOpeningToMiddleGamePst();

    while (1) {
        fgets(line, sizeof(line), stdin);
        fillArgs(line, args, &numArgs);

        if (strcmp(args[0], "uci") == 0) {
            printf("id name %s\n", BOT_NAME);
            fflush(stdout);
            printf("uciok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "ucinewgame") == 0) {
            //clearTranspositionTable();
            //initTranspositionTable();
            initOpeningToMiddleGamePst();
            printf("readyok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "isready") == 0) {
            printf("readyok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "quit") == 0) {
            //clearTranspositionTable();
            break;
        } else if (numArgs >= 2 && strcmp(args[0], "position") == 0 && strcmp(args[1], "startpos") == 0) {
            isWhite = true;
            setupPositionWithMoveList(position, initialBoardCopy, &isWhite, args, numArgs, history);
        } else if (strcmp(args[0], "go") == 0) {
            char uciMove[6];
            int currentPly = position->currentPly;
            if(currentPly < 4) { // hardcode first moves
                playOpening(position, currentPly);
            } else {
                Move bestMove;
                searchBestMove(position, &bestMove, atoi(isWhite ? args[2] : args[4]), isWhite);
                moveToUciMove(&bestMove, uciMove);
                printf("bestmove %s\n", uciMove);
            }
            fflush(stdout);
        }
    }
}