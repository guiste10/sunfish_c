#include <stdio.h>
#include "pieceSquareTables.h"
#include "uci.h"
#include "debug.h"

int main() {
    initPst();
    //playUci();
    findBestMoveTimeStamped();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
