#include "position.h"
#include "constants.h"
#include "chessBoard.h"
#include "move.h"
#include "pieceSquareTables.h"
#include "debug.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void initPosition(Position* position, char* boardCopy, char* boardSrc){
    copyBoard(boardCopy, boardSrc);
    position->board = boardCopy;
    position->score = 0;
    position->wc[0] = true;
    position->wc[1] = true;
    position->bc[0] = true;
    position->bc[1] = true;
    position->ep = 0;
    position->kp = 0;
}

Position* duplicatePosition(Position* source, Position* target, char* targetBoard){
    target->score = source->score;
    target->wc[0] = source->wc[0];
    target->wc[1] = source->wc[1];
    target->bc[0] = source->bc[0];
    target->bc[1] = source->bc[1];
    target->ep = source->ep;
    target->kp = source->kp;
    target->board = targetBoard;
    copyBoard(target->board, source->board);
    return target;
}

int genMoves(Position* position, Move moves[MAX_BRANCHING_FACTOR]) { // For each friendly piece, iterate through each possible 'ray' of moves as defined in the 'directions' map. The rays are broken e.g. by captures or immediately in case of pieces such as knights.
    int moveIndex = 0;
    for (int i = 0; i <SIZE ; i++) {
        char p = position->board[i];
        if (!isupper(p))
            continue;
        int* pieceDirections = (int*)DIRECTIONS[pieceIndexes[p]];
        for (int dirIndex = 0; *(pieceDirections + dirIndex) != ARRAY_END; dirIndex++) {
            int d = *(pieceDirections + dirIndex);
            for (int j = i + d; j >= 0 && j < SIZE; j += d) {
                char q = position->board[j];
                if (isspace(q) || isupper(q)) // Stay inside the board, and off friendly pieces
                    break;
                if (p == 'P') { // Pawn move, double move and capture
                    if ((d == NORTH || d == NORTH + NORTH) && q != '.')
                        break;
                    if (d == NORTH + NORTH && (i < A1 + NORTH || position->board[i + NORTH] != '.'))
                        break;
                    if ((d == NORTH + WEST || d == NORTH + EAST) && q == '.' && j != position->ep
                    && j != position->kp - 1 && j != position->kp && j != position->kp + 1) // for castling check detection
                        break;
                    if (j >= A8 && j <= H8) { // If we move to the last row, we can be anything
                        for (int promotion = Q; promotion > P ; promotion--)
                            createMove(i, j, promotion, &moves[moveIndex++]);
                        break;
                    }
                }
                createMove(i, j, NO_PROMOTION, &moves[moveIndex++]); // Move it
                if (strchr("PNK", p) != NULL || islower(q)) // Stop crawlers from sliding, and sliding after captures
                    break;
                if (i == A1 && position->board[j + EAST] == 'K' && position->wc[0]) // Castling, by sliding the rook next to the king
                    createMove(j + EAST, j + WEST, NO_PROMOTION, &moves[moveIndex++]);
                if (i == H1 && position->board[j + WEST] == 'K' && position->wc[1])
                    createMove(j + WEST, j + EAST, NO_PROMOTION, &moves[moveIndex++]);
            }
        }
    }
    return moveIndex;
}

int value(const Position *position, const Move *move) {
    int i = move->i;
    int j = move->j;
    int prom = move->prom;
    char p = position->board[i];
    char q = position->board[j];

    int friendlyPieceIndex = pieceIndexes[p];
    int score = pst[friendlyPieceIndex][j] - pst[friendlyPieceIndex][i];

    if (islower(q)) { // Capture
        int enemyPieceIndex = pieceIndexes[q];
        score += pst[enemyPieceIndex][119 - j];
    }

    if (abs(j - position->kp) < 2) { // position->kp = square where opponent's rook is after castling, 0 if he has not just castled
        score += pst[K][119 - j]; // Castling check detection, add king's value to score to make it >= Mate_lower because castling was illegal (king, or the 2 other adjacent squares were attacked)
    }

    if (p == 'K' && abs(i - j) == 2) { // Castling
        score += pst[R][(i + j) / 2];
        score -= pst[R][j < i ? A1 : H1];
    }

    if (p == 'P') {
        if (A8 <= j && j <= H8) { // promotion
            score += pst[prom][j] - pst[P][j];
        }
        if (j == position->ep) { // en passant
            score += pst[P][SIZE - 1 - (j + SOUTH)];
        }
    }

    return score;
}

void doMove(Position* position, Move* move, Position* newPosition, char* newBoard) {
    Position newPos; // Copy board representation
    newPos.board = newBoard;
    *newPosition = newPos;
    copyBoard(newPosition->board, position->board);

    int i = move->i, j = move->j;
    char prom = PIECES[move->prom];
    char p = position->board[i];

    newPosition->wc[0] = position->wc[0];
    newPosition->wc[1] = position->wc[1];
    newPosition->bc[0] = position->bc[0];
    newPosition->bc[1] = position->bc[1];
    newPosition->ep = 0;
    newPosition->kp = 0;
    newPosition->score = position->score + value(position, move);

    newPosition->board[j] = newPosition->board[i]; // Actual move
    newPosition->board[i] = '.';

    if (i == A1) { // Castling rights, we move the rook or capture the opponent's
        newPosition->wc[0] = false;
    }
    if (i == H1) {
        newPosition->wc[1] = false;
    }
    if (j == A8) {
        newPosition->bc[0] = false;
    }
    if (j == H8) {
        newPosition->bc[1] = false;
    }

    if (p == 'K') {  // Castling
        newPosition->wc[0] = false;
        newPosition->wc[1] = false;
        if (abs(j - i) == 2) {
            newPosition->kp = (i + j) / 2; // 96 if short castle, 94 if long castle
            newPosition->board[(j < i) ? A1 : H1] = '.';
            newPosition->board[newPosition->kp] = 'R';
        }
    }

    if (p == 'P') { // Pawn promotion, double move, and en passant capture
        if (A8 <= j && j <= H8) {
            newPosition->board[j] = prom;
        }
        if (j - i == 2 * NORTH) {
            newPosition->ep = i + NORTH;
        }
        if (j == position->ep) {
            newPosition->board[j + SOUTH] = '.';
        }
    }
}


void rotate(Position* position, bool nullMove) {
    for (int i = 0; i < SIZE / 2; i++) { // rotate board
        char temp = position->board[i];
        position->board[i] = position->board[SIZE - i - 1];
        position->board[SIZE - i - 1] = temp;
    }
    for (int i = 0; i < SIZE; i++) { // swap cases
        char *piece = &(position->board[i]);
        if(isalpha(*piece)) {
            *piece = isupper(*piece) ? tolower(*piece) : toupper(*piece);
        }
    }

    position->score = -position->score; // Update other attributes
    position->ep = (position->ep && !nullMove) ? (119 - position->ep) : 0;
    position->kp = (position->kp && !nullMove) ? (119 - position->kp) : 0;
}