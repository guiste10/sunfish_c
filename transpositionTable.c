#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "transpositionTable.h"

#define TABLE_SIZE_LOG2 20 // Use a table size of 2^20 (adjust as needed)

TranspositionEntry* transpositionTable = NULL;

const int LOWER = 0;
const int EXACT = 1;
const int UPPER = 2;

void initTranspositionTable() {
    // Allocate memory for the transposition table on the heap
    transpositionTable = (TranspositionEntry*)malloc(sizeof(TranspositionEntry) * (1 << TABLE_SIZE_LOG2));

    if (transpositionTable == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    // Initialize the transposition table entries
    memset(transpositionTable, 0, sizeof(TranspositionEntry) * (1 << TABLE_SIZE_LOG2));
}

void clearTranspositionTable() {
    // Free the allocated memory for the transposition table
    if (transpositionTable != NULL) {
        free(transpositionTable);
        transpositionTable = NULL;
    }
}

// Hash function to map a position to an index in the transposition table
unsigned int hashFunction(uint64_t hash) {
    return (unsigned int)(hash & ((1 << TABLE_SIZE_LOG2) - 1));
}

TranspositionEntry* lookupTT(uint64_t hash) {
    unsigned int index = hashFunction(hash);
    TranspositionEntry* entry = &transpositionTable[index];

    if (entry->hash == hash) {
        return entry; // Found a matching entry
    } else {
        return NULL; // No matching entry found
    }
}

void saveScore(uint64_t hash, int depth, int score, int type, Move bestMove) {
    unsigned int index = hashFunction(hash);

    // Store the entry if it's deeper or has the same depth but a better type
    TranspositionEntry* entry = &transpositionTable[index];

    if (depth > entry->depth || (depth == entry->depth && type != entry->type)) {
        entry->hash = hash;
        entry->depth = depth;
        entry->score = score;
        entry->type = type;
        entry->bestMove = bestMove;
    }
}