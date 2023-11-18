#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H

#include "constants.h"
#include <stdbool.h>

typedef struct {
    int from;
    int to;
    int prom;
    char pieceTo;
    int moveValue;
    int moveType;
} Move;

extern const Move nullMove;

extern const int promotionType;
extern const int captureType;
extern const int killerType; // non capturing!
extern const int nonCaptureType;

void createMove(int from, int to, int prom, char pieceTo, Move* move);
void moveToUciMove(const Move *move, char uciMove[6]);
void uciMoveToMove(const char uciMove[6], Move *move, bool isWhite);
bool isCapture(const Move *move, const char *board, int ep);
bool equalMoves(const Move* moveA, const Move* moveB);
int compareMoves(const void* x, const void* y);
#endif //SUNFISH_C_MOVE_H
