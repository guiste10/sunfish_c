//
// Created by neiringu on 28-05-23.
//
#include "position.h"
#include "constants.h"
#include "map.h"
#include "chessBoard.h"
#include "arraylist.h"
#include "move.h"
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>

Position* initPosition(){
    Position *position = malloc(sizeof(Position));
    position->board = board;
    position->score = 0;
    position->wc[0] = true;
    position->wc[1] = true;
    position->bc[0] = true;
    position->bc[1] = true;
    return position;
}

ArrayList* gen_moves(Position * position, Map* directions) {
    // For each of our pieces, iterate through each possible 'ray' of moves,
    // as defined in the 'directions' map. The rays are broken e.g. by
    // captures or immediately in case of pieces such as knights.
    ArrayList* moves = createArrayList();
    for (int i = 0; i <SIZE ; i++) {
        char p = position->board[i];
        if (!isupper(p))
            continue;
        char pieceIdentifier[2] = {p, '\0'};
        int* pieceDirections = (int*)(uintptr_t)map_get(directions, pieceIdentifier);
        for (int dirIndex = 0; dirIndex != ARRAY_END; dirIndex++) {
            int d = *(pieceDirections + dirIndex);
            for (int j = i + d; j >= 0 && j < SIZE; j += d) {
                char q = position->board[j];
                // Stay inside the board, and off friendly pieces
                if (isspace(q) || isupper(q))
                    break;
                // Pawn move, double move and capture
                if (p == 'P') {
                    if ((d == N || d == N + N) && q != '.')
                        break;
                    if (d == N + N && (i < A1 + N || position->board[i + N] != '.'))
                        break;
                    if ((d == N + W || d == N + E) && q == '.' &&
                        j != position->ep) //)&& j != position->kp && j != position->kp - 1 && j != position->kp + 1)
                        break;
                    // If we move to the last row, we can be anything
                    if (j >= A8 && j <= H8) {
                        for (int promIndex = 0; promIndex < NUM_PROMOTIONS; promIndex++)
                            arrayListAdd(moves, createMove(i, j, PROMOTIONS[promIndex]));
                        break;
                    }
                }
                // Move it
                arrayListAdd(moves, createMove(i, j, NO_PROMOTION));
                // Stop crawlers from sliding, and sliding after captures
                if (strchr("PNK", p) != NULL || islower(q))
                    break;
                // Castling, by sliding the rook next to the king
                if (i == A1 && position->board[j + E] == 'K' && position->wc[0])
                    arrayListAdd(moves, createMove(j + E, j + W, NO_PROMOTION));
                if (i == H1 && position->board[j + W] == 'K' && position->wc[1])
                    arrayListAdd(moves, createMove(j + W, j + E, NO_PROMOTION));
            }
        }
    }
    return moves;
}

