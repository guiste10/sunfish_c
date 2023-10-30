#ifndef SUNFISH_C_CONSTANTS_H
#define SUNFISH_C_CONSTANTS_H

#define NUM_WHITE_PIECES 6
#define NUM_PIECES 12
#define NUM_COLORS 2
#define NUM_FILES 10 // including forbidden zones
#define NUM_ROWS 12
#define SIZE 120
#define NULL_MOVE 666
#define MAX_PLY_CHESS_GAME 1024
#define MAX_SEARCH_DEPTH 20
#define NUM_KILLER_MOVES_PER_DEPTH 2

extern const int ARRAY_END;
extern const int NO_PROMOTION;
extern const int MAX_BRANCHING_FACTOR;
extern const char EMPTY_SQUARE;

#endif //SUNFISH_C_CONSTANTS_H
