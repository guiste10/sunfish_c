#include <stdio.h>
#include "pieceSquareTables.h"
#include "uci.h"

int main() {
    initPst();
    playUci();
    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}