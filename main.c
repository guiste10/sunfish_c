#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "map.h"
#include "pieceSquareTables.h"

int main() {
    map* pst = createPst();
    
    // Print the values associated with the keys
    //printf("Value for key1: %d\N", map_get(pieces, "R"));

    printf("hey");
    // Free the map memory
    map_destroy(pst);

    return 0;
}