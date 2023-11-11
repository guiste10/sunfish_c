#include <stdio.h>
#include "debug.h"
#include "uci.h"

int main() {
    //char uciPosition[] = "position startpos moves d2d4 g7g6 c2c4 f8g7 g1f3 g8f6 c1f4 d7d5 e2e3 e8g8 f1d3 f6h5 f4g3";
    //findBestMoveFromUciPosition(uciPosition);

    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
