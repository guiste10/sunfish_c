
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "position.h"
#include "constants.h"
#include "search.h"
#include "debug.h"
#include "pieceSquareTables.h"

const int MAX_ARGS = 1000;
const char BOT_NAME[] = "Sunfish_c";

void playUci(){
    char line[1000];
    char* args[MAX_ARGS];
    bool isWhite = true;
    Position pos;
    Position* position = &pos;
    char initialBoardCopy[SIZE];

    while (1) {
        fgets(line, sizeof(line), stdin);
        int numArgs = 0;
        char *token = strtok(line, " \n");
        while (token != NULL && numArgs < MAX_ARGS) {
            args[numArgs++] = token;
            token = strtok(NULL, " \n");
        }

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
            initPosition(position, initialBoardCopy);
            for (int ply = 0; ply < numArgs - 3; ply++) {
                int i, j;
                char prom;
                char from [3], to[3];
                char *uciMove = args[3 + ply];
                char uciProm = *(uciMove+4);
                strncpy(from, uciMove, 2);
                from[2] = '\0';
                strncpy(to, uciMove + 2, 2);
                to[2] = '\0';
                i = parse(from);
                j = parse(to);
                prom = uciProm == '\0' ? NO_PROMOTION : toupper(uciProm); // to check
                if (!isWhite) {
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
                isWhite = !isWhite;

                //printCharArray(position->board, SIZE);
            }
        } else if (strcmp(args[0], "go") == 0) {
            Move* bestMove = searchBestMove(position);
            int i = bestMove->i;
            int j = bestMove->j;
            char prom = bestMove->prom;
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

//            int wtime, btime, winc, binc;
//            int i;
//            // Extracting values for wtime, btime, winc, binc
//            for (i = 2; i < numArgs; i += 2) {
//                int val = atoi(args[i]);
//                if (i == 2) {
//                    wtime = val / 1000;
//                } else if (i == 4) {
//                    btime = val / 1000;
//                } else if (i == 6) {
//                    winc = val / 1000;
//                } else if (i == 8) {
//                    binc = val / 1000;
//                }
//            }
//
//            // Adjusting values based on len(hist) % 2
//            if (len(hist) % 2 == 0) {
//                wtime = btime;
//                winc = binc;
//            }
//
//            // Calculating think
//            int think = (wtime / 40) + winc;
//            if (think > (wtime / 2 - 1)) {
//                think = wtime / 2 - 1;
//            }
//
//            time_t start = time(NULL);
//            char moveStr[5] = "";
//            bool moveStrFound = false;
//            int depth, gamma, score, i, j;
//            char prom;
//
//            while (1) {
//                // Perform search and update depth, gamma, score, move values
//
//                if (score >= gamma) {
//                    if (moveStrFound)
//                        break;
//
//                    if (len(hist) % 2 == 0) {
//                        i = 119 - i;
//                        j = 119 - j;
//                    }
//                    printMove(i, j, prom);
//                    sprintf(moveStr, "%c%c%c", i + 'a', j + '1', prom);
//                    printf("info depth %d score cp %d pv %s\n", depth, score, moveStr);
//                }
//
//                if (moveStrFound && time(NULL) - start > think * 0.8)
//                    break;
//            }
//
//            printf("bestmove %s\n", moveStr[0] != '\0' ? moveStr : "(none)");
        }
    }
}