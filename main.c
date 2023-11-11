#include <stdio.h>
#include "uci.h"

int main() {
    //char debug[] = "position startpos moves e2e4";
    //findBestMoveFromUciPosition(debug);

    playUci();

    // Flush the output stream
    printf("\n");
    fflush(stdout);
    return 0;
}
