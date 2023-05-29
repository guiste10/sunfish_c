//
// Created by neiringu on 28-05-23.
//
#include "position.h"
#include "constants.h"
#include "map.h"
#include "chessBoard.h"
#include "arraylist.h"
#include "move.h"
#include "pieceSquareTables.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

Position* initPosition(){
    Position *position = malloc(sizeof(Position));
    position->board = (char*)initialBoard;
    position->score = 0;
    position->wc[0] = true;
    position->wc[1] = true;
    position->bc[0] = true;
    position->bc[1] = true;
    return position;
}

ArrayList* genMoves(Position * position) {
    // For each of our pieces, iterate through each possible 'ray' of moves,
    // as defined in the 'directions' map. The rays are broken e.g. by
    // captures or immediately in case of pieces such as knights.
    ArrayList* moves = createArrayList();
    for (int i = 0; i <SIZE ; i++) {
        char p = position->board[i];
        if (!isupper(p))
            continue;
        int* pieceDirections = (int*)DIRECTIONS[p];
        for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
            int d = *(pieceDirections + dirIndex);
            for (int j = i + d; j >= 0 && j < SIZE; j += d) {
                char q = position->board[j];
                // Stay inside the board, and off friendly pieces
                if (isspace(q) || isupper(q))
                    break;
                // Pawn move, double move and capture
                if (p == 'P') {
                    if ((d == NORTH || d == NORTH + NORTH) && q != '.')
                        break;
                    if (d == NORTH + NORTH && (i < A1 + NORTH || position->board[i + NORTH] != '.'))
                        break;
                    if ((d == NORTH + WEST || d == NORTH + EAST) && q == '.' &&
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
                if (i == A1 && position->board[j + EAST] == 'K' && position->wc[0])
                    arrayListAdd(moves, createMove(j + EAST, j + WEST, NO_PROMOTION));
                if (i == H1 && position->board[j + WEST] == 'K' && position->wc[1])
                    arrayListAdd(moves, createMove(j + WEST, j + EAST, NO_PROMOTION));
            }
        }
    }
    return moves;
}

void rotate(Position* position, bool nullMove) {
    int boardSize = 120;
    for (int i = 0; i < boardSize / 2; i++) {
        char temp = position->board[i];
        position->board[i] = position->board[boardSize - i - 1];
        position->board[boardSize - i - 1] = temp;

        // Swap case if it is an alphabetic character
        if (isalpha(position->board[i])) {
            position->board[i] = (char)toupper(position->board[i]);
        } else if (isupper(position->board[i])) {
            position->board[i] = (char)tolower(position->board[i]);
        }

        if (isalpha(position->board[boardSize - i - 1])) {
            position->board[boardSize - i - 1] = (char)toupper(position->board[boardSize - i - 1]);
        } else if (isupper(position->board[boardSize - i - 1])) {
            position->board[boardSize - i - 1] = (char)tolower(position->board[boardSize - i - 1]);
        }
    }

    // Update other attributes
    position->score = -position->score;
    position->ep = (position->ep && !nullMove) ? (119 - position->ep) : 0;
    position->kp = (position->kp && !nullMove) ? (119 - position->kp) : 0;
}

void doMove(Position* position, Move* move, char* newBoard) {
    // Copy board representation
    Position newPosition;
    newPosition.board = newBoard;
    copyBoard(newBoard, position->board);
    // Init helper variables
    int i = move->i, j = move->j;
    char prom = move->prom;
    char p = position->board[i];

    // Copy variables and reset ep and kp
    newPosition.wc[0] = position->wc[0];
    newPosition.wc[1] = position->wc[1];
    newPosition.bc[0] = position->bc[0];
    newPosition.bc[1] = position->bc[1];
    newPosition.ep = 0;
    newPosition.kp = 0;
    newPosition.score = position->score + 0; //value(move);  // Assuming value() function exists

    // Actual move
    newPosition.board[j] = newPosition.board[i];
    newPosition.board[i] = '.';

    // Castling rights, we move the rook or capture the opponent's
    if (i == A1) {
        newPosition.wc[0] = false;
    }
    if (i == H1) {
        newPosition.wc[1] = false;
    }
    if (j == A8) {
        newPosition.bc[0] = false;
    }
    if (j == H8) {
        newPosition.bc[1] = false;
    }

    // Castling
    if (p == 'K') {
        newPosition.wc[0] = false;
        newPosition.wc[1] = false;
        if (abs(j - i) == 2) {
            newPosition.kp = (i + j) / 2; // 96 if short castle, 94 if long castle
            newPosition.board[(j < i) ? A1 : H1] = '.';
            newPosition.board[newPosition.kp] = 'R';
        }
    }

    // Pawn promotion, double move, and en passant capture
    if (p == 'P') {
        if (A8 <= j && j <= H8) {
            newPosition.board[j] = prom;
        }
        if (j - i == 2 * NORTH) {
            newPosition.ep = j;
        }
        if (j == position->ep) {
            newPosition.board[j + SOUTH] = '.';
        }
    }

    // We rotate the new position, so it's ready for the next player
    rotate(&newPosition, false);
}

int value(const Position *position, const Move *move) {
    int i = move->i;
    int j = move->j;
    char prom = move->prom;
    char p = position->board[i];
    char q = position->board[j];
    int score = pst[p][j] - pst[p][i];

    // Capture
    if (islower(q)) {
        score += pst[toupper(q)][119 - j];
    }

    // Castling check detection
    if (abs(j - position->kp) < 2) {
        score += pst[K][119 - j];
    }

    // Castling
    if (p == 'K' && abs(i - j) == 2) {
        score += pst[R][(i + j) / 2];
        score -= pst[R][j < i ? A1 : H1];
    }

    // Special pawn stuff
    if (p == 'P') {
        if (A8 <= j && j <= H8) {
            score += pst[prom][j] - pst[P][j];
        }
        if (j == position->ep) {
            score += pst[P][119 - (j + SOUTH)];
        }
    }

    return score;
}



