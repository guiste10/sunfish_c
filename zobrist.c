#include <stdint.h>
#include "zobrist.h"
#include "constants.h"
#include "position.h"
#include "chessBoard.h"
#include "randomUnsigned64bitIntegers.h"

#define NUM_CASTLING_SIDES 2
#define NUM_FILES 10

uint64_t blackToMoveHash = UINT64_MAX;
uint64_t castlingRightsHash[NUM_COLORS][NUM_CASTLING_SIDES];
uint64_t enPassantFileHash[NUM_FILES];
uint64_t pieceHashForSquares[NUM_PIECES][SIZE];  // 120 pieces squares, 12 piece types (P, p, B, p, ...) => 1440 random hashes

void initializeZobristHashes() {
    int index = 0;
    blackToMoveHash = randomIntegers[index++];

    for (int color = 0; color < NUM_COLORS; color++) {
        for (int castlingSide = 0; castlingSide < NUM_CASTLING_SIDES; castlingSide++) {
            castlingRightsHash[color][castlingSide] = randomIntegers[index++];
        }
    }

    for (int file = 0; file < NUM_FILES; file++) {
        enPassantFileHash[file] = randomIntegers[index++];
    }

    for (int pieceIndex = 0; pieceIndex < NUM_PIECES; pieceIndex++) {
        for (int square = 0; square < SIZE; square++) {
            pieceHashForSquares[pieceIndex][square] = randomIntegers[index++];
        }
    }
}

void setInitialZobristHash(Position* position) {
    initializeZobristHashes();
    uint64_t hash = 0;
    char *board = position->board;
    if (!position->turn){
        hash ^= blackToMoveHash;
    }
    for (int square = 0; square < SIZE; square++) {
        char piece = board[square];
        if (piece != '.') {
            int pieceIndex = PIECE_INDEXES_IGNORE_COLOR[piece];
            hash ^= pieceHashForSquares[pieceIndex][square];
        }
    }
    position->hash = hash;
}