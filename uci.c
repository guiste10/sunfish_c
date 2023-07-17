
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "position.h"
#include "constants.h"
#include "search.h"
#include "debug.h"
#include "chessBoard.h"
#include "utils.h"

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

void setupPosition(Position* position, char* initialBoardCopy, bool* isWhite, char* uciPosition[MAX_ARGS], int numArgs){
    initPosition(position, initialBoardCopy, (char*)initialBoard);
    *isWhite = true;
    for (int ply = 0; ply < numArgs - 3; ply++) {
        int i, j;
        int prom;
        char from[3], to[3];
        char *uciMove = uciPosition[3 + ply];
        char uciProm = *(uciMove+4);
        strncpy(from, uciMove, 2);
        from[2] = '\0';
        strncpy(to, uciMove + 2, 2);
        to[2] = '\0';
        i = parse(from);
        j = parse(to);
        prom = uciProm == '\0' ? NO_PROMOTION : indexOf(PIECES, toupper(uciProm));
        if (!*isWhite) {
            i = 119 - i;
            j = 119 - j;
        }
        Move* move = createMove(i, j, prom);
        Position* duplicate = duplicatePosition(position);
        doMove(duplicate, move, position, position->board);
        free(duplicate->board);
        free(duplicate);
        rotate(position, false);
        free(move);
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
    char initialBoardCopy[SIZE];

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
            setupPosition(position, initialBoardCopy, &isWhite, args, numArgs);
        } else if (strcmp(args[0], "go") == 0) {
            Move* bestMove = searchBestMove(position);
            int i = bestMove->i;
            int j = bestMove->j;
            char prom = PIECES[bestMove->prom];
            free(bestMove);
            if (!isWhite) {
                i = 119 - i;
                j = 119 - j;
            }
            char from[3], to[3];
            render(i, from);
            render(j, to);
            char uciMove[6] = {from[0], from[1], to[0], to[1], prom, '\0'};
            printf("bestmove %s\n", uciMove);
            fflush(stdout);
        }
    }
}