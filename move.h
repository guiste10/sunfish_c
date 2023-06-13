#ifndef SUNFISH_C_MOVE_H
#define SUNFISH_C_MOVE_H
typedef struct {
    int i;
    int j;
    char prom;
} Move;

Move* createMove(int i, int j, char prom);
void render(int index, char* result);
int parse(const char* c);
void printMove(Move move, char board[]);

#endif //SUNFISH_C_MOVE_H
