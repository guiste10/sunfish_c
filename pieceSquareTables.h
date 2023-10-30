#ifndef SUNFISH_C_PIECESQUARETABLES_H
#define SUNFISH_C_PIECESQUARETABLES_H
#include "constants.h"
#include <stdbool.h>

extern const int MATE_LOWER;
extern const int MATE_UPPER;
extern int pieceValues[NUM_WHITE_PIECES];
extern int PST[6][SIZE];

void initPst();
bool isEndGame(const char *board);
void setEndGamePST();

#endif //SUNFISH_C_PIECESQUARETABLES_H
