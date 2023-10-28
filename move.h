#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"
#include <stdbool.h>

typedef struct {
    int moveType; // used only for null move and move ordering
    int from;
    int to;
    int prom;
    char pieceTo;
} Move;

extern char* currentBoard; // for sorting the moves

extern const int nullType;
extern const int unknownType;
extern const int pvType;
extern const int winningCaptureType;
extern const int killerType; // non capturing!
extern const int equalCaptureType;
extern const int losingCaptureType;
extern const int promotionType;
extern const int nonCaptureType;

extern const Move nullMove;

void createMove(int from, int to, int prom, char pieceTo, Move* move);
void moveToUciMove(const Move *move, char uciMove[6]);
void uciMoveToMove(const char uciMove[6], Move *move, bool isWhite);
bool equalMoves(const Move* moveA, const Move* moveB);
void sortMoves(Move moves[], int numMoves, char *board);
#endif //SUNFISH_C_MOVE_H
