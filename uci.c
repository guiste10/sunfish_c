#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "position.h"
#include "constants.h"
#include "search.h"
#include "chessBoard.h"

const int MAX_ARGS = 1000;
const char BOT_NAME[] = "Sunfish_c";

void fillArgs(char* line, char* args[MAX_ARGS], int* numArgs){
    *numArgs = 0;
    char *token = strtok(line, " \n");
    while (token != NULL && *numArgs < MAX_ARGS) {
        args[(*numArgs)++] = token;
        token = strtok(NULL, " \n");
    }
}

void setupPositionWithMoveList(Position* position, bool* isWhite, char *uciMoves[1000], int numArgs){
    initPosition(position, (char*)initialBoard);
    for (int ply = 0; ply < numArgs - 3; ply++) {
        char *uciMove = uciMoves[3 + ply];
        Move move;
        uciMoveToMove(uciMove, &move);
        doMove(position, &move);
        *isWhite = !*isWhite;
    }
}

void playUci(){
    char line[1000];
    char* args[MAX_ARGS];
    int numArgs;
    bool isWhite = true;
    Position pos;
    Position* position = &pos;

    while (1) {
        fgets(line, sizeof(line), stdin);
        fillArgs(line, args, &numArgs);

        if (strcmp(args[0], "uci") == 0) {
            printf("id name %s\n", BOT_NAME);
            fflush(stdout);
            printf("uciok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "isready") == 0) {
            printf("readyok\n");
            fflush(stdout);
        } else if (strcmp(args[0], "quit") == 0) {
            break;
        } else if (numArgs >= 2 && strcmp(args[0], "position") == 0 && strcmp(args[1], "startpos") == 0) {
            setupPositionWithMoveList(position, &isWhite, args, numArgs);
        } else if (strcmp(args[0], "go") == 0) {
            Move best;
            Move* bestMove = &best;
            searchBestMove(position, bestMove, atoi(isWhite ? args[2] : args[4]), isWhite);
            char uciMove[6];
            moveToUciMove(bestMove, uciMove);
            printf("bestmove %s\n", uciMove);
            fflush(stdout);
        }
    }
}