#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"
#include "pieceSquareTables.h"
#include "tpMove.h"
#include "tpScore.h"

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
    initPosition(position, initialBoardCopy, (char *) initialBoard, history);
    for (int ply = 0; ply < numArgs - 3; ply++) {
        char *uciMove = uciMoves[3 + ply];
        Move move;
        uciMoveToMove(uciMove, &move, *isWhite);
        move.moveValue = value(position, &move);
        *isWhite = !*isWhite;
        doMove(position, &move);
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
        memset(args, 0, sizeof(char*) * MAX_ARGS);
        fillArgs(line, args, &numArgs);

        if (strcmp(args[0], "uci") == 0) {
            printf("id name %s\n", BOT_NAME);
            fflush(stdout);
            printf("uciok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "ucinewgame") == 0) {
            initTpScore();
            initTpMove();
            initOpeningToMiddleGamePst();
            fflush(stdout);
        } else if (strcmp(args[0], "isready") == 0) {
            printf("readyok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "quit") == 0) {
            clearTpScore();
            clearTpMove();
            break;
        } else if (numArgs >= 2 && strcmp(args[0], "position") == 0 && strcmp(args[1], "startpos") == 0) {
            isWhite = true;
            setupPositionWithMoveList(position, initialBoardCopy, &isWhite, args, numArgs, history);
        } else if (strcmp(args[0], "go") == 0) {
            char uciMove[6];
            char* timeLeftArg = isWhite ? args[2] : args[4];
            int timeLeft = timeLeftArg == NULL ? 999999 : atoi(timeLeftArg);
            Move bestMove = searchBestMove(position, timeLeft);
            moveToUciMove(&bestMove, uciMove);
            printf("bestmove %s\n", uciMove);
            fflush(stdout);
            clearTpScore();
            clearTpMove();
            initTpScore();
            initTpMove();
        }
    }
}